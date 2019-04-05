/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DescendBras.h"

#include "Logger.h"
#include "Robot.h"

#include "subsystems/Bras.h"


DescendBras::DescendBras()
	 : Command(__func__)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBras);
	m_logger.set_min_level(wpi::WPI_LOG_DEBUG1);
}

// Called just before this Command runs the first time
void DescendBras::Initialize()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	Robot::m_sysBras.DisablePID();
}

// Called repeatedly when this Command is scheduled to run
void DescendBras::Execute()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	Robot::m_sysBras.setSpeedDescent();
}

// Make this return true when this Command no longer needs to run execute()
bool DescendBras::IsFinished()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	return false;
}

// Called once after isFinished returns true
void DescendBras::End()
{
	WPI_INFO(m_logger, GetName() << " " << __func__ << "Enable PID");
	Robot::m_sysBras.EnablePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DescendBras::Interrupted()
{
	WPI_INFO(m_logger, GetName() << " " << __func__ << "Enable PID");
	Robot::m_sysBras.EnablePID();
}
