/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AvancerCrochet.h"

#include "Logger.h"
#include "Robot.h"

#include "subsystems/Crochet.h"


AvancerCrochet::AvancerCrochet()
	 : Command(__func__)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysCrochet);
	m_speed = 1.0; //vitesse a tester
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void AvancerCrochet::Initialize()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}

// Called repeatedly when this Command is scheduled to run
void AvancerCrochet::Execute()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	setSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool AvancerCrochet::IsFinished()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	if (IsTimedOut())
	{
		//WPI_WARNING(OI::m_logger, GetName() << " Delai d'attente de " << llvm::format("%5.2f", m_timeout) << " secondes expire.");
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void AvancerCrochet::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	setSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AvancerCrochet::Interrupted()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	setSpeed(0.0);
}

void AvancerCrochet::setSpeed(double speed)
{
	// Enregistrer la nouvelle vitesse désirée (point de consigne).
	Robot::m_sysCrochet.setSpeed(speed);
}
