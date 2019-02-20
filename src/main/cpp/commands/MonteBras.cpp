/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MonteBras.h"

#include "Logger.h"
#include "Robot.h"

#include "subsystems/Bras.h"


MonteBras::MonteBras()
	 : Command(__func__)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBras);
	m_timeout = 1;  // timeout de 1 seconde a tester
	m_speed = 0.5; //vitesse a tester
	SetTimeout(m_timeout);
	m_logger.set_min_level(wpi::WPI_LOG_DEBUG1);
}

// Called just before this Command runs the first time
void MonteBras::Initialize()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);

	setSpeed();
}

// Called repeatedly when this Command is scheduled to run
void MonteBras::Execute()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
}

// Make this return true when this Command no longer needs to run execute()
bool MonteBras::IsFinished()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	if (IsTimedOut())
	{
		WPI_DEBUG4(m_logger, "MonteBras::IsFinished");
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void MonteBras::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	// Robot::m_sysBras.setSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MonteBras::Interrupted()
{
	WPI_WARNING(m_logger, GetName() << " " << __func__);
	// Robot::m_sysBras.setSpeed(0.0);
}

void MonteBras::setSpeed()
{
	// Robot::m_sysBras.setSpeed(m_speed);
}
