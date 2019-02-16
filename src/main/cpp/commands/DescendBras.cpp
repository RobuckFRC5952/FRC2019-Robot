/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DescendBras.h"

#include "subsystems/Bras.h"

DescendBras::DescendBras() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());

}

// Called just before this Command runs the first time
void DescendBras::Initialize() 
{
  WPI_DEBUG3(m_logger,"DescendBras::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void DescendBras::Execute() 
{
  WPI_DEBUG4(m_logger,"DescendBras::Execute");
}

// Make this return true when this Command no longer needs to run execute()
bool DescendBras::IsFinished() 
{
  WPI_DEBUG4(m_logger,"DescendBras::IsFinished"); 
  return false; 
}

// Called once after isFinished returns true
void DescendBras::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DescendBras::Interrupted() {}
