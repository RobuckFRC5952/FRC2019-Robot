/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Robot.h
/// \brief Le %Robot basé sur \b frc::TimedRobot.

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <wpi/Logger.h>
#include <frc/DriverStation.h>

#include "Logger.h"
#include "OI.h"
#include "subsystems/BaseMobile.h"
#include "subsystems/Bras.h"
#include "subsystems/Pince.h"
#include "subsystems/Crochet.h"


class Robot : public frc::TimedRobot
{
 public:
	static OI m_oi;
	static sysBaseMobile m_sysBaseMobile;
	static sysBras m_sysBras; //subsystem bras mobile
	static sysPince m_sysPince; //subsystem pince
   static sysCrochet m_sysCrochet;
	enum frc::DriverStation::Alliance Rouge_ou_Bleu;

	wpi::Logger m_logger{log_func};


	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

 private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command *m_autonomousCommand = nullptr;
	frc::SendableChooser<frc::Command *> m_chooser;
};
