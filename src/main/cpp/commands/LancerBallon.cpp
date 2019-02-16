/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LancerBallon.h"

#include "Logger.h"
#include "Robot.h"

#include "subsystems/Pince.h"


cmdLancerBallon::cmdLancerBallon()
	 : Command(__func__)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysPince);
	m_logger.set_min_level(wpi::WPI_LOG_DEBUG1);
}

// Called just before this Command runs the first time
void cmdLancerBallon::Initialize()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	m_speed = 1.0; //vitesse a tester
	setSpeed(m_speed);
}

// Called repeatedly when this Command is scheduled to run
void cmdLancerBallon::Execute()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
}

// Make this return true when this Command no longer needs to run execute()
bool cmdLancerBallon::IsFinished()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	return false;
}

// Called once after isFinished returns true
void cmdLancerBallon::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	setSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdLancerBallon::Interrupted()
{
	WPI_WARNING(m_logger, GetName() << " " << __func__);
	setSpeed(0.0);
}

void cmdLancerBallon::setSpeed(double speed)
{
	m_speed = speed;
	Robot::m_sysPince.setSpeed(m_speed);
}
