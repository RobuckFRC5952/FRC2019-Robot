/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rampe.h"

#include "Logger.h"

sysRampe::sysRampe()
	 : Subsystem(__func__)
	 , m_logger(log_func)
{
	AddChild("Mot", m_RampeMoteur);

	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

void sysRampe::InitDefaultCommand()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void sysRampe::setSpeed(double speed)
{
	WPI_DEBUG3(m_logger, "m_RampeMoteur::setSpeed vitesse: " << speed);
	m_RampeMoteur.Set(speed);
}
