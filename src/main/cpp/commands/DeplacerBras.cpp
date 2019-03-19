/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeplacerBras.h"

#include <wpi/Format.h>

#include "Logger.h"
#include "Robot.h"
#include "subsystems/Bras.h"

cmdDeplacerBras::cmdDeplacerBras(double position)
	 : Command(__func__)
	 , m_Position(position)
	 , m_lastTime(0.0)
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBras);

	m_logger.set_min_level(wpi::WPI_LOG_DEBUG3);
}

// Called just before this Command runs the first time
void cmdDeplacerBras::Initialize()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
	m_lastTime = TimeSinceInitialized();
}

// Called repeatedly when this Command is scheduled to run
void cmdDeplacerBras::Execute()
{
	if (((TimeSinceInitialized() - m_lastTime) > 0.25) ||
	    (m_logger.min_level() <= wpi::WPI_LOG_DEBUG4))
	{
		WPI_DEBUG2(m_logger, GetName() << " " << __func__ << wpi::format(" %5.2f %5.2f", m_Position, TimeSinceInitialized()));
		m_lastTime = TimeSinceInitialized();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool cmdDeplacerBras::IsFinished()
{
	return TimeSinceInitialized() > 5.0;
}

// Called once after isFinished returns true
void cmdDeplacerBras::End()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdDeplacerBras::Interrupted()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
}
