/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LancerBallon.h"

#include "Robot.h"

cmdLancerBallon::cmdLancerBallon()
	 : Command(__func__)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
  	m_speed = 0.5; //vitesse a tester
  	Requires(&Robot::m_sysBras);
}

// Called just before this Command runs the first time
void cmdLancerBallon::Initialize()
{
  WPI_DEBUG3(m_logger,"cmdLancerBallon::Initialize");

  setSpeed();
}

// Called repeatedly when this Command is scheduled to run
void cmdLancerBallon::Execute()
{
  WPI_DEBUG4(m_logger,"cmdLancerBallon::Execute");
}

// Make this return true when this Command no longer needs to run execute()
bool cmdLancerBallon::IsFinished()
{
	WPI_DEBUG4(m_logger,"cmdLancerBallon::IsFinished");
	return false;
}

// Called once after isFinished returns true
void cmdLancerBallon::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdLancerBallon::Interrupted()
{
}


void cmdLancerBallon::setSpeed()
{
  Robot::m_sysPince.setSpeed(m_speed);
}
