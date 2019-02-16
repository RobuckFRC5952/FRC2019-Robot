/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "commands/DeployerRampe.h"

#include "Robot.h"
#include "subsystems/Rampe.h"


DeployerRampe::DeployerRampe(double speed)
	 : Command(__func__), m_speed(speed)
{
	Requires(&Robot::m_Rampe);
}

// Called just before this Command runs the first time
void DeployerRampe::Initialize()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
}

// Called repeatedly when this Command is scheduled to run
void DeployerRampe::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DeployerRampe::IsFinished()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	return false;
}

// Called once after isFinished returns true
void DeployerRampe::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployerRampe::Interrupted()
{

}
