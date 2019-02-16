/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MonteBras.h"

MonteBras::MonteBras() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_timeout = 1; // timeout de 1 seconde a tester
  m_speed = 0.5; //vitesse a tester
  SetTimeout(m_timeout);
}

// Called just before this Command runs the first time
void MonteBras::Initialize() 
{
  WPI_DEBUG3(m_logger,"MonteBras::Initialize");

  setSpeed(m_speed);
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
		//WPI_WARNING(OI::m_logger, GetName() << ": Delai d'attente de " << llvm::format("%5.2f", m_timeout) << " secondes expire.");
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



void MonteBras::setSpeed(double speed)
{
	// Enregistrer la nouvelle vitesse dÃ©sirÃ©e (point de consigne).
	m_speed = speed;

}
