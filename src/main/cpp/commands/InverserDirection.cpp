/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/InverserDirection.h"

#include "Logger.h"
#include "Robot.h"


InverserDirection::InverserDirection()
	 : InstantCommand(__func__)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBaseMobile);

	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called once when the command executes
void InverserDirection::Initialize()
{
	eDirection direction = Robot::m_sysBaseMobile.getDirection();
	if (direction == eDirection::Bras)
	{
		direction = eDirection::Crochet;
		WPI_DEBUG(m_logger, GetName() << " " << __func__ << " direction: Crochet");
	}
	else
	{
		direction = eDirection::Bras;
		WPI_DEBUG(m_logger, GetName() << " " << __func__ << " direction: Bras");
	}
	Robot::m_sysBaseMobile.setDirection(direction);
}
