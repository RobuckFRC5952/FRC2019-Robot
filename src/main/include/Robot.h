/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Robot.h
/// \brief Le %Robot basé sur \b frc::TimedRobot.

#include <cameraserver/CameraServer.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"

#include "subsystems/BaseMobile.h"
#include "subsystems/Bras.h"
#include "subsystems/Pince.h"
#include "subsystems/Crochet.h"
#include "subsystems/Rampe.h"

#include "commands/DeplacerBaseMobile.h"
#include "commands/GrpStation1.h"
#include "commands/GrpStation2.h"
#include "commands/GrpStation3.h"

namespace frc
{
	class Command;
}

class Robot : public frc::TimedRobot
{
 public:
	static OI m_oi;
	static sysBaseMobile m_sysBaseMobile;
	static sysBras       m_sysBras;
	static sysPince      m_sysPince;
	static sysCrochet    m_sysCrochet;
	static sysRampe      m_sysRampe;

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

	/// Selecteur du mode autonome.
	enum class eAutonomousMode
	{
		TeleopVideo,
		StartPosision,
		Chooser,
	};
	frc::SendableChooser<eAutonomousMode const *> m_auto_mode;
	const eAutonomousMode m_teleop_video   = eAutonomousMode::TeleopVideo;
	const eAutonomousMode m_start_posotion = eAutonomousMode::StartPosision;
	const eAutonomousMode m_cmd_chooser    = eAutonomousMode::Chooser;

	frc::SendableChooser<frc::Command *> m_chooser;
	cmdDeplacerBaseMobile m_cmdDeplacerBaseMobile {1.0};
	cmdGrpStation1 m_cmdGrpStation1;
	cmdGrpStation2 m_cmdGrpStation2;
	cmdGrpStation3 m_cmdGrpStation3;

	cs::UsbCamera m_camera_bras;
	bool m_useCameraBras {true};
	bool m_lastCameraBras {true};
	cs::UsbCamera m_camera_crochet;
	bool m_useCameraCrochet {true};
	bool m_lastCameraCrochet {true};
	cs::VideoSink m_server;
	frc::CameraServer * m_cam_server;

	eDirection m_last_direction {eDirection::Bras};

	/// Logger de la classe \c Robot.
	wpi::Logger m_logger;
};
