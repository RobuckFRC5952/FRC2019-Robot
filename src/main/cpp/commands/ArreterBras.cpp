/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ArreterBras.h"

#include <algorithm>

#include <wpi/Format.h>

#include "Logger.h"
#include "Robot.h"
#include "subsystems/Bras.h"

cmdArreterBras::cmdArreterBras()
	 : Command(__func__)
	 , m_acceleration(sysBras::accelMax)	// FIXME TBD
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBras);

	// Ajuster le niveau de messages à la Console.
	m_logger.set_min_level(wpi::WPI_LOG_INFO);

	SetInterruptible(false);
}

// Called just before this Command runs the first time
void cmdArreterBras::Initialize()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
	setSpeedSP(0.0);
}

// Called repeatedly when this Command is scheduled to run
void cmdArreterBras::Execute()
{
	// Chercher la position actuelle calculée.
	m_position = m_mrua->getIntegratedPosition();
	m_speed    = m_mrua->getIntegratedSpeed();

	// Restreindre la position par les limites du sous-système.
	double position = std::max(sysBras::posMin, std::min(m_position, sysBras::posMax));

	Robot::m_sysBras.setPositionSP(position);

	// Log à chaque demi-seconde, ou si le logger log.
	double time = TimeSinceInitialized();
	if (((time - m_lastTime) > 0.5) ||
	    (m_logger.min_level() <= wpi::WPI_LOG_DEBUG4))
	{
		WPI_DEBUG1(m_logger, GetName() << " " << __func__ << wpi::format(" m_position: %5.2f", m_position) << ", m_speed: " << wpi::format("%5.2f", m_speed));
		m_lastTime = time;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool cmdArreterBras::IsFinished()
{
	// Terminer la commande quand on atteint la vitesse désirée.
	if (((m_mrua->getAcceleration() >= 0.0) && (m_speed >= m_speed_sp)) ||
	    ((m_mrua->getAcceleration() <  0.0) && (m_speed <= m_speed_sp)))
	{
		WPI_DEBUG1(m_logger, GetName() << " " << __func__ << " Vitesse de " << wpi::format("%5.2f", m_speed_sp) << " atteinte a la position " << wpi::format("%5.2f", m_position));
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void cmdArreterBras::End()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdArreterBras::Interrupted()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
}


void cmdArreterBras::setSpeedSP(double speed_sp)
{
	// Enregistrer la nouvelle vitesse désirée (point de consigne).
	m_speed_sp = speed_sp;

	// Trouver la position et la vitesse actuelle du sous-système.
	// double current_position = Robot::m_sysBras.getPositionFB();
	double current_position = Robot::m_sysBras.getPositionSP();	// Comme ça, l'erreur ne tombe pas à zéro.
	double current_speed    = Robot::m_sysBras.getSpeedFB();

	// Trouver le signe de l'accélération. Il est en fonction de la vitesse 
	// désirée par rapport à la vitesse actuelle.
	double acceleration = std::copysign(m_acceleration, m_speed_sp - current_speed);

	// Utiliser un nouvel object Mrua pour calculer la vitesse et la position en fonction du temps.
	m_mrua.reset(new Mrua(acceleration, current_speed, current_position));
	WPI_DEBUG1(m_logger, GetName() << " Mrua: " << *m_mrua << ", " << "Speed: " << wpi::format("%5.2f", m_speed_sp));

	m_mrua->Initialize();
}
