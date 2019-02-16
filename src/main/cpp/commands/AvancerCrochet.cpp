/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AvancerCrochet.h"
#include "subsystems/Crochet.h"
#include "Robot.h"

AvancerCrochet::AvancerCrochet() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_timeout = 1; // timeout de 1 seconde a tester
  m_speed = 0.5; //vitesse a tester
  SetTimeout(m_timeout);
  Requires(&Robot::m_sysCrochet); 
}

// Called just before this Command runs the first time
void AvancerCrochet::Initialize() {
WPI_DEBUG(m_logger, "AvancerCrochet::Initialize");
setSpeed(m_speed);
}

// Called repeatedly when this Command is scheduled to run
void AvancerCrochet::Execute() {
WPI_DEBUG2(m_logger, "AvancerCrochet::Execute");
} 

// Make this return true when this Command no longer needs to run execute()
bool AvancerCrochet::IsFinished() {
    if (IsTimedOut())
	{
		//WPI_WARNING(OI::m_logger, GetName() << ": Delai d'attente de " << llvm::format("%5.2f", m_timeout) << " secondes expire.");
		return true;
	}
  return false; 
  }

// Called once after isFinished returns true
void AvancerCrochet::End() {
WPI_DEBUG(m_logger, "AvancerCrochet::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AvancerCrochet::Interrupted() {}

void AvancerCrochet::setSpeed(double speed)
{
	// Enregistrer la nouvelle vitesse dÃƒÂ©sirÃƒÂ©e (point de consigne).
	m_speed = speed;
  Robot::m_sysCrochet.setSpeed(m_speed);
}
