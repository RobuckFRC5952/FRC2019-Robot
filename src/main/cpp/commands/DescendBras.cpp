/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DescendBras.h"

#include "Robot.h"

DescendBras::DescendBras() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_timeout = 1; // timeout de 1 seconde a tester
  m_speed = 0.5; //vitesse a tester
  SetTimeout(m_timeout);
  Requires(&Robot::m_sysBras);
}

// Called just before this Command runs the first time
void DescendBras::Initialize() 
{
  WPI_DEBUG3(m_logger,"DescendBras::Initialize");

  setSpeed();
}

// Called repeatedly when this Command is scheduled to run
void DescendBras::Execute() 
{
  WPI_DEBUG4(m_logger,"DescendBras::Execute");
}

// Make this return true when this Command no longer needs to run execute()
bool DescendBras::IsFinished() 
{
  if (IsTimedOut())
  {
  WPI_DEBUG4(m_logger,"DescendBras::IsFinished"); 
	return true;
	}
  return false;
}

// Called once after isFinished returns true
void DescendBras::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DescendBras::Interrupted() {}



void DescendBras::setSpeed()
{
  Robot::m_sysBras.setSpeed(m_speed);
}
