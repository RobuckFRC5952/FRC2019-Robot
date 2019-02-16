/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MonteBras.h"

#include "Logger.h"
#include "Robot.h"

MonteBras::MonteBras() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_timeout = 1; // timeout de 1 seconde a tester
  m_speed = -0.5; //vitesse a tester
  SetTimeout(m_timeout);
  Requires(&Robot::m_sysBras);
	m_logger.set_min_level(wpi::WPI_LOG_DEBUG3);
}

// Called just before this Command runs the first time
void MonteBras::Initialize() 
{
  WPI_DEBUG3(m_logger,"MonteBras::Initialize");

  setSpeed();
}

// Called repeatedly when this Command is scheduled to run
void MonteBras::Execute() 
{
  WPI_DEBUG4(m_logger,"MonteBras::Execute");
}

// Make this return true when this Command no longer needs to run execute()
bool MonteBras::IsFinished() 
{ 
  if (IsTimedOut())
	{
    WPI_DEBUG4(m_logger,"MonteBras::IsFinished");
		return true;
	}
  return false; 
  }

// Called once after isFinished returns true
void MonteBras::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MonteBras::Interrupted() {}



void MonteBras::setSpeed()
{
  Robot::m_sysBras.setSpeed(m_speed);
}
