/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeplacerBaseMobile.h"

#include <wpi/Format.h>
#include <wpi/Logger.h>

#include "Logger.h"
#include "Robot.h"
#include "subsystems/BaseMobile.h"


cmdDeplacerBaseMobile::cmdDeplacerBaseMobile(double distance)
	 : cmdDeplaceMoteur(Robot::m_sysBaseMobile, 0.0, Robot::m_sysBaseMobile.getSpeedMax(), Robot::m_sysBaseMobile.getAccelMax())
	 , m_distance(distance)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBaseMobile);

	// Renommer la commande cmdDeplaceMoteur par cmdDeplacerBaseMobile.
	SetName("DeplacerBaseMobile");

	// Ajuster le niveau de messages à la Console.
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void cmdDeplacerBaseMobile::Initialize()
{
	setDistance(m_distance);
	WPI_INFO(m_logger, GetName() << " Deplacement de " << wpi::format("%5.2f", m_distance) << " metres.");
	cmdDeplaceMoteur::Initialize();
}

// Called repeatedly when this Command is scheduled to run
void cmdDeplacerBaseMobile::Execute()
{
	cmdDeplaceMoteur::Execute();
}

// Make this return true when this Command no longer needs to run execute()
bool cmdDeplacerBaseMobile::IsFinished()
{
	return cmdDeplaceMoteur::IsFinished();
}

// Called once after isFinished returns true
void cmdDeplacerBaseMobile::End()
{
	cmdDeplaceMoteur::End();
	WPI_INFO(m_logger, GetName() << " Vitesse termine a " << wpi::format("%5.2f", 0.0)); // TODO
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdDeplacerBaseMobile::Interrupted()
{
	cmdDeplaceMoteur::Interrupted();
	WPI_INFO(m_logger, GetName() << " Interruption de la commande");
}
