/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <array>
#include <string>

#include <frc/commands/Command.h>
#include <frc/commands/Scheduler.h>
#include <frc/DriverStation.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Logger.h"


OI Robot::m_oi;

sysBaseMobile Robot::m_sysBaseMobile;
sysBras       Robot::m_sysBras;
sysPince      Robot::m_sysPince;
sysCrochet    Robot::m_sysCrochet;
sysRampe      Robot::m_sysRampe;

void Robot::RobotInit()
{
	m_logger.SetLogger(log_func);
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
	WPI_INFO(m_logger, "ESMR ROBUCK FRC 2019");

	m_chooser.SetDefaultOption("Deplacer",  &m_cmdDeplacerBaseMobile);
	m_chooser.AddOption(       "Station 1", &m_cmdGrpStation1);
	m_chooser.AddOption(       "Station 2", &m_cmdGrpStation2);
	m_chooser.AddOption(       "Station 3", &m_cmdGrpStation3);
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

	m_auto_mode.SetDefaultOption("Teleop Video",   &m_teleop_video);
	m_auto_mode.AddOption(       "Start Position", &m_start_posotion);
	m_auto_mode.AddOption(       "Auto Modes",     &m_cmd_chooser);
	frc::SmartDashboard::PutData("Modes Autonomes", &m_auto_mode);

	// TODO Le Bras DOIT être en position élevée.
	m_sysBras.resetPosition();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit()
{
	WPI_INFO(m_logger, __func__);

	// Désactiver les régulateur même si après DisableInit, il n'y a pas de 
	// commandes envoyées aux moteurs.  Au AutonomousInit ou TeleopInit, on veut
	// refaire un EnablePID pour prendre la distance courrante des encodeurs et 
	// avoir une erreur minimale.
	m_sysBaseMobile.DisablePID();
	m_sysBras.DisablePID();
}

void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit()
{
	eAutonomousMode const mode_autonome = *(m_auto_mode.GetSelected());
	if (mode_autonome == eAutonomousMode::TeleopVideo)
	{
		/// Réactiver la commande par défaut, au cas où elle avait été désactivé en mode autonome.
		m_sysBaseMobile.InitDefaultCommand();
		m_sysBaseMobile.DisablePID();
	}
	else
	{
		// Changer la commande par défaut du sous-système BaseMobile à Immobile.
		m_sysBaseMobile.SetImmobileCommand();

		/// Activer le régulateur du sous-système.
		m_sysBaseMobile.EnablePID();
	}

	/// Activer les autres régulateurs des sous-systèmes.
	m_sysBras.EnablePID();

	// Arrêter la commande en cours.
	frc::Command * cmd = m_sysBaseMobile.GetCurrentCommand();
	if (cmd)
	{
		cmd->Cancel();
	}
	
	switch (mode_autonome)
	{
		case eAutonomousMode::TeleopVideo:
		{
			WPI_INFO(m_logger, __func__ << " Teleop Video mode");
			m_autonomousCommand = nullptr;
		}
		break;

		case eAutonomousMode::StartPosision:
		{
			// Trouver l'alliance et la station/position du robot.
			frc::DriverStation & ds = frc::DriverStation::GetInstance();
			enum frc::DriverStation::Alliance team_alliance = ds.GetAlliance();
			std::array<std::string, 3> const alliance_str {"Red", "Blue", "Invalid"};
			int team_location = ds.GetLocation();
			WPI_INFO(m_logger, __func__ << " Start Posision Team Station: '" << alliance_str[team_alliance] << team_location << "'.");

			switch (team_location)
			{
				case 1:
					m_autonomousCommand = &m_cmdGrpStation1;
				break;

				case 2:
					m_autonomousCommand = &m_cmdGrpStation2;
				break;

				case 3:
					m_autonomousCommand = &m_cmdGrpStation3;
				break;

				default:
					WPI_WARNING(m_logger, __func__ << " Unsupported team station.");
				break;
			}
		}
		break;

		case eAutonomousMode::Chooser:
		{
			m_autonomousCommand = m_chooser.GetSelected();
			WPI_INFO(m_logger, __func__ << " Chooser command: '" << m_autonomousCommand->GetName() << "'.");
		}
		break;
	}

	if (m_autonomousCommand != nullptr)
	{
		m_autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic()
{
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
	WPI_INFO(m_logger, __func__);

	/// Réactiver la commande par défaut, au cas où elle avait été désactivé en mode autonome.
	m_sysBaseMobile.InitDefaultCommand();
	frc::Command * cmd = m_sysBaseMobile.GetCurrentCommand();
	if (cmd)
	{
		cmd->Cancel();
	}

	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (m_autonomousCommand != nullptr)
	{
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
	m_sysBaseMobile.DisablePID();
	m_sysBras.EnablePID();
}

void Robot::TeleopPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	m_sysBaseMobile.PutSmartDashboard();
	m_sysBras.PutSmartDashboard();
}

void Robot::TestPeriodic()
{
}

#ifndef RUNNING_FRC_TESTS
int main()
{
	return frc::StartRobot<Robot>();
}
#endif
