/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Crochet.h"

#include <algorithm>

#include <wpi/Format.h>

#include "Logger.h"


sysCrochet::sysCrochet()
	 : Subsystem(__func__)
	, m_logger(log_func)
{
	AddChild("Mot",       m_CrochetMoteur);
	AddChild("LimSwBas",  m_limitSwitchBas);
	AddChild("LimSwHaut", m_limitSwitchHaut);

	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

void sysCrochet::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void sysCrochet::setSpeed(double speed) 
{
	bool isLimitBasReached  = m_limitSwitchBas.Get();
	bool isLimitHautReached = m_limitSwitchHaut.Get();

	if (isLimitBasReached)
	{
		// Ceci va empêcher le moteur de continuer à descendre le crochet quand il atteint sa fin de course.
		// Il pourra quand même remonter même si la limite switch est active.
		speed = std::max(speed, 0.0);
	}

	if (isLimitHautReached)
	{
		// Ceci va empêcher le moteur de continuer à monter le crochet quand il atteint sa fin de course.
		// Il pourra quand même redescendre même si la limite switch est active.
		speed = std::min(0.0, speed);
	}

	WPI_DEBUG2(m_logger, "speed:" << wpi::format("%5.2f", speed));
	m_CrochetMoteur.Set(speed);
}