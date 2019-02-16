/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Logger.h"
#include "subsystems/Bras.h"


sysBras::sysBras()
	 : Subsystem(__func__)
	 , m_logger(log_func)
{
	m_logger.set_min_level(wpi::WPI_LOG_DEBUG3);
}

void sysBras::InitDefaultCommand()
{
	WPI_DEBUG3(m_logger,"sysBras::InitDefaultCommand");
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void sysBras::setSpeed(double speed)
{
	WPI_DEBUG3(m_logger,"sysBras::setSpeed vitesse: " << speed);

}