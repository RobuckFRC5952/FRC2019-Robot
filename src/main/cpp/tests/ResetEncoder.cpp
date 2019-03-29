/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tests/ResetEncoder.h"

#include "Robot.h"

cmdResetEncoder::cmdResetEncoder()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBaseMobile);
}

// Called just before this Command runs the first time
void cmdResetEncoder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void cmdResetEncoder::Execute()
{
	Robot::m_sysBaseMobile.resetPosition();
}

// Make this return true when this Command no longer needs to run execute()
bool cmdResetEncoder::IsFinished() { return true; }

// Called once after isFinished returns true
void cmdResetEncoder::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdResetEncoder::Interrupted() {}
