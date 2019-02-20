/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/InverserDirection.h"

#include "Robot.h"


InverserDirection::InverserDirection() {
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::m_sysBaseMobile);
}

// Called once when the command executes
void InverserDirection::Initialize()
{
	if (m_direction == eDirection::Bras)
	{
		m_direction = eDirection::Crochet;
	}
	else
	{
		m_direction = eDirection::Bras;
	}
	Robot::m_sysBaseMobile.setDirection(m_direction);
}
