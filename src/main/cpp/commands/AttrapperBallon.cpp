/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AttrapperBallon.h"

#include "Robot.h"

AttrapperBallon::AttrapperBallon() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_speed = -0.5; //vitesse a tester
  Requires(&Robot::m_sysBras);
}

// Called just before this Command runs the first time
void AttrapperBallon::Initialize() 
{
  WPI_DEBUG3(m_logger,"AttrapperBallon::Initialize");

  setSpeed();
}

// Called repeatedly when this Command is scheduled to run
void AttrapperBallon::Execute() 
{
  WPI_DEBUG4(m_logger,"AttrapperBallon::Execute");
}

// Make this return true when this Command no longer needs to run execute()
bool AttrapperBallon::IsFinished() 
{ 
  WPI_DEBUG4(m_logger,"AttrapperBallon::IsFinished");
	return false;
}

// Called once after isFinished returns true
void AttrapperBallon::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AttrapperBallon::Interrupted() {}


void AttrapperBallon::setSpeed()
{
  Robot::m_sysPince.setSpeed(m_speed);
}
