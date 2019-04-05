/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AttrapperBallon.h"

#include "Logger.h"
#include "Robot.h"

#include "subsystems/Pince.h"


AttrapperBallon::AttrapperBallon()
	 : Command(__func__)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysPince);
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void AttrapperBallon::Initialize()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	m_speed = 1.0;
	setSpeed(m_speed);
}

// Called repeatedly when this Command is scheduled to run
void AttrapperBallon::Execute()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
}

// Make this return true when this Command no longer needs to run execute()
bool AttrapperBallon::IsFinished()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	return false;
}

// Called once after isFinished returns true
void AttrapperBallon::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	setSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AttrapperBallon::Interrupted()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	setSpeed(0.0);
}

void AttrapperBallon::setSpeed(double speed)
{
	m_speed = speed;
	Robot::m_sysPince.setSpeed(m_speed);
}
