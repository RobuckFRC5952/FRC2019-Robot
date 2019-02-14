/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "../include/Robot.h"
#include "commands/DeployerRampe.h"
#include "../include/subsystems/Rampe.h"

DeployerRampe::DeployerRampe(double speed)
  : Command ()
  , m_speed(0.0)
{
  Requires(&Robot::m_Rampe);
}

// Called just before this Command runs the first time
void DeployerRampe::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DeployerRampe::Execute() {}
  
// Make this return true when this Command no longer needs to run execute()
bool DeployerRampe::IsFinished() { return false; }


// Called once after isFinished returns true
void DeployerRampe::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployerRampe::Interrupted() {}
