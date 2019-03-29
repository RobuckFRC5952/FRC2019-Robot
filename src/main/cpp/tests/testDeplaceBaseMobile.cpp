/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tests/testDeplaceBaseMobile.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/Format.h>

#include "cinematique/Mrua.h"
#include "Robot.h"
#include "subsystems/BaseMobile.h"


char const * testDeplaceBaseMobile::m_key_distance= "Distance";
char const * testDeplaceBaseMobile::m_key_speed_max = "Vitesse";
char const * testDeplaceBaseMobile::m_key_acceleration = "Acceleration";

char const * testDeplaceBaseMobile::m_key_kP = "kP";
char const * testDeplaceBaseMobile::m_key_kI = "kI";
char const * testDeplaceBaseMobile::m_key_kD = "kD";
char const * testDeplaceBaseMobile::m_key_kF = "kF";


testDeplaceBaseMobile::testDeplaceBaseMobile()
: cmdDeplacerBaseMobile(0.0)
, m_distance(0.0)
, m_speed_max(1.0)
, m_acceleration(1.0)
{
	// Renommer la commande cmdDeplaceMoteur par cmdTestDeplaceMoteur.
	SetName(__func__);

	frc::SmartDashboard::PutNumber(m_key_distance,     m_distance);
	frc::SmartDashboard::PutNumber(m_key_speed_max,    m_speed_max);
	frc::SmartDashboard::PutNumber(m_key_acceleration, m_acceleration);

	frc::SmartDashboard::PutNumber(m_key_kP, 0.0);
	frc::SmartDashboard::PutNumber(m_key_kI, 0.0);
	frc::SmartDashboard::PutNumber(m_key_kD, 0.0);
	frc::SmartDashboard::PutNumber(m_key_kF, 0.0);

	// Ajuster le niveau de messages à la Console.
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void testDeplaceBaseMobile::Initialize()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);

	m_distance     = frc::SmartDashboard::GetNumber(m_key_distance,     0.0);
	m_speed_max    = frc::SmartDashboard::GetNumber(m_key_speed_max,    m_speed_max);
	m_acceleration = frc::SmartDashboard::GetNumber(m_key_acceleration, m_acceleration);
	setDistance(m_distance);
	setSpeedMax(m_speed_max);
	setAcceleration(m_acceleration);

	WPI_DEBUG(m_logger, "distance "     << wpi::format("%5.2f", m_distance)
	                <<  ", speed max: " << wpi::format("%5.2f", m_speed_max)
	                <<  ", accel: "     << wpi::format("%5.2f", m_acceleration));

	double kP = frc::SmartDashboard::GetNumber(m_key_kP, 0.0);	// 0.2
	double kI = frc::SmartDashboard::GetNumber(m_key_kI, 0.0);
	double kD = frc::SmartDashboard::GetNumber(m_key_kD, 0.0);
	double kF = frc::SmartDashboard::GetNumber(m_key_kF, 0.0);
	Robot::m_sysBaseMobile.EnablePID(kP, kI, kD, kF);

	cmdDeplaceMoteur::Initialize();
}

// Called repeatedly when this Command is scheduled to run
void testDeplaceBaseMobile::Execute()
{
	cmdDeplaceMoteur::Execute();
}

// Make this return true when this Command no longer needs to run execute()
bool testDeplaceBaseMobile::IsFinished()
{
	return cmdDeplaceMoteur::IsFinished();
}

// Called once after isFinished returns true
void testDeplaceBaseMobile::End()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	Robot::m_sysBaseMobile.DisablePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void testDeplaceBaseMobile::Interrupted()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	Robot::m_sysBaseMobile.DisablePID();
}
