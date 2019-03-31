/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ArcadeDriveJoystick.h"
#include <wpi/Format.h>

#include "Logger.h"
#include "Robot.h"
#include "subsystems/BaseMobile.h"


cmdArcadeDriveJoystick::cmdArcadeDriveJoystick(frc::Joystick & joystick, sysBaseMobile & sys_base_mobile)
	 : Command(__func__)
	 , m_joystick(joystick)
	 , m_sysBaseMobile(sys_base_mobile)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&m_sysBaseMobile);

	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void cmdArcadeDriveJoystick::Initialize()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	m_lastTime = TimeSinceInitialized();
}

// Called repeatedly when this Command is scheduled to run
void cmdArcadeDriveJoystick::Execute()
{
	double gainVitesse  = 1.0;
	double gainRotation = 1.0;
	if (m_joystick.GetTrigger())
	{
		gainVitesse = 0.5;
		gainRotation = 0.75;
	}
	double speed = m_joystick.GetY();
	double rotation = m_joystick.GetX() * 0.75;
	m_sysBaseMobile.ArcadeDrive(speed * gainVitesse, rotation * gainRotation);

	if (((TimeSinceInitialized() - m_lastTime) > 0.5) ||
	    (m_logger.min_level() <= wpi::WPI_LOG_DEBUG4))
	{
		WPI_DEBUG2(m_logger, "speed: "      << wpi::format("%5.2f", speed) 
		                  << ", rotation: " << wpi::format("%5.2f", rotation));
		m_lastTime = TimeSinceInitialized();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool cmdArcadeDriveJoystick::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void cmdArcadeDriveJoystick::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdArcadeDriveJoystick::Interrupted()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}
