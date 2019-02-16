/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeployerRampe.h"

#include "Logger.h"
#include "Robot.h"


DeployerRampe::DeployerRampe()
	 : Command(__func__)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_logger.set_min_level(wpi::WPI_LOG_DEBUG1);
}

// Called just before this Command runs the first time
void DeployerRampe::Initialize()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}

// Called repeatedly when this Command is scheduled to run
void DeployerRampe::Execute()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
}

// Make this return true when this Command no longer needs to run execute()
bool DeployerRampe::IsFinished()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__);
	return false;
}

// Called once after isFinished returns true
void DeployerRampe::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployerRampe::Interrupted()
{
	WPI_WARNING(m_logger, GetName() << " " << __func__);
}
