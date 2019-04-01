/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ArcadeDriveImmobile.h"

#include "Logger.h"
#include "Robot.h"
#include "subsystems/BaseMobile.h"

cmdArcadeDriveImmobile::cmdArcadeDriveImmobile(sysBaseMobile &sys_base_mobile)
	 : Command(__func__)
	 , m_sysBaseMobile(sys_base_mobile)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&m_sysBaseMobile);

	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void cmdArcadeDriveImmobile::Initialize()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}

// Called repeatedly when this Command is scheduled to run
void cmdArcadeDriveImmobile::Execute()
{
	m_sysBaseMobile.ArcadeDrive(0.0, 0.0);
}

// Make this return true when this Command no longer needs to run execute()
bool cmdArcadeDriveImmobile::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void cmdArcadeDriveImmobile::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdArcadeDriveImmobile::Interrupted()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}
