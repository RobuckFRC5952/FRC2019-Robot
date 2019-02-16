/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Pince.h"

sysPince::sysPince()
	 : Subsystem(__func__)
{
}

void sysPince::InitDefaultCommand()
{
	WPI_DEBUG3(m_logger,"sysPince::InitDefaultCommand");
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void sysPince::setSpeed(double speed)
{
	WPI_DEBUG3(m_logger,"sysPince::setSpeed vitesse: " << speed);
}
