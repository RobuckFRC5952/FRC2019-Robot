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

// TODO Generic, pass pointer to ISubSystem
cmdDeplacerBras::cmdDeplacerBras(double position_sp)
	 : cmdDeplaceMoteur(0.0, sysBras::speedMax, sysBras::accelMax)
	 , m_position_sp(position_sp)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBras);

	// Renommer la commande cmdDeplaceMoteur par cmdDeplacerBras.
	SetName("DeplacerBras");

	// Ajuster le niveau de messages à la Console.
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void cmdDeplacerBras::Initialize()
{

	// Se déplacer de la position courrante à la consigne (m_position_sp).
	double current_position = Robot::m_sysBras.getPositionFB();
	setDistance(m_position_sp - current_position);
	WPI_INFO(m_logger, GetName() << " Position commence de " << wpi::format("%5.2f", current_position)
	                             << " a "                    << wpi::format("%5.2f", m_position_sp));
	cmdDeplaceMoteur::Initialize();
}

// Called repeatedly when this Command is scheduled to run
void cmdDeplacerBras::Execute()
{
	cmdDeplaceMoteur::Execute();
}

// Make this return true when this Command no longer needs to run execute()
bool cmdDeplacerBras::IsFinished()
{
	return cmdDeplaceMoteur::IsFinished();
}

// Called once after isFinished returns true
void cmdDeplacerBras::End()
{
	cmdDeplaceMoteur::End();
	double position_sp = Robot::m_sysBras.getPositionSP();
	WPI_INFO(m_logger, GetName() << " Position termine a " << wpi::format("%5.2f", position_sp));
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdDeplacerBras::Interrupted()
{
	cmdDeplaceMoteur::Interrupted();
	double position_sp = Robot::m_sysBras.getPositionSP();
	WPI_INFO(m_logger, GetName() << " Interruption de la commande, position a " << wpi::format("%5.2f", position_sp));
}
