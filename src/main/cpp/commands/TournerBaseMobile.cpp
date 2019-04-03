/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TournerBaseMobile.h"

#include <wpi/Format.h>

#include "cinematique/Deplacement.h"
#include "cinematique/Mrua.h"
#include "Logger.h"
#include "Robot.h"
#include "subsystems/BaseMobile.h"


cmdTournerBaseMobile::cmdTournerBaseMobile(double rotation)
	: Command(__func__)
	, m_rotation(rotation)
	, m_rotation_speed_max(Robot::m_sysBaseMobile.getRotationSpeedMax())
	, m_rotation_acceleration(Robot::m_sysBaseMobile.getRotationAccelMax())
	, m_phase(0)
	, m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBaseMobile);

	// Renommer la commande cmdDeplaceMoteur par cmdDeplacerBaseMobile.
	SetName("TournerBaseMobile");

	// Ajuster le niveau de messages à la Console.
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void cmdTournerBaseMobile::Initialize()
{
	WPI_INFO(m_logger, GetName() << " Rotation de " << wpi::format("%5.2f", m_rotation) << " degres.");

	if (std::abs(m_rotation) <= 0.0)  // TODO 
	{
		WPI_WARNING(m_logger, GetName() << " Rotation trop petite.");
		Cancel();
		return;
	}

	// Trouver le profil de vitesse.
	Deplacement d;

	// L'object de type Deplacement peut lancer des exceptions de type: std::exception.
	// Il faut les attrapper sinon l'application se termine automatiquement (et brutalement).
	try
	{
		d.setSpeedMax(m_rotation_speed_max);
		d.setAcceleration(m_rotation_acceleration);
		m_profile = d.getSpeedProfile(m_rotation, 0.0, 0.0);
		WPI_DEBUG1(m_logger, GetName() << " " << print_vt_profile(m_profile).str());
	}
	catch (std::exception const & e)
	{
		WPI_WARNING(m_logger, GetName() << " " << e.what());
		Cancel();
		return;
	}
	// Si pour une raison la quantité d'éléments dans le vecteur n'est pas 3 ou 4.
	if ((m_profile.size() != 3) && (m_profile.size() != 4))
	{
		WPI_WARNING(m_logger, GetName() << " Erreur dans le nombre d'elements de la variable m_profile.");
		Cancel();
		return;
	}
	// Si le déplacement est trop court, ignorer.
	if (m_profile.back().m_time - m_profile.front().m_time <= 0.004)
	{
		WPI_WARNING(m_logger, GetName() << " Temps du profile trop petit.");
		Cancel();
		return;
	}

	// Voir la classe 'Deplacement' pour la signification de t1, t2, v1, etc.
	m_phase = 0;
	double const & v0 = m_profile[m_phase + 0].m_speed;
	double const & v1 = m_profile[m_phase + 1].m_speed;
	double const & t0 = m_profile[m_phase + 0].m_time;
	double const & t1 = m_profile[m_phase + 1].m_time;

	WPI_DEBUG(m_logger, GetName() << " " << __func__ << " Vitesse de la phase " << m_phase
	                              << " de "      << wpi::format("%5.2f", v0)
	                              << " a  "      << wpi::format("%5.2f", v1)
	                              << " pendant " << wpi::format("%6.3f", t1 - t0) << " sec.");

	// TODO rotation absolue?

	// Trouver le signe de l'accélération. Il est en fonction de la vitesse 
	// désirée par rapport à la vitesse actuelle.
	double acceleration = std::copysign(m_rotation_acceleration, v1 - v0);

	// Utiliser un nouvel object Mrua pour calculer la vitesse et la position en fonction du temps.
	m_mrua.reset(new Mrua(acceleration, v0, 0.0));
	WPI_DEBUG1(m_logger, GetName() << " Mrua: " << *m_mrua);

	m_lastTime = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void cmdTournerBaseMobile::Execute()
{
	if (IsCanceled())
	{
		return;
	}

	// Vérifier si une phase du profil de vitesse est atteint.
	double time = TimeSinceInitialized();
	if (time >= m_profile[m_phase + 1].m_time)
	{
		WPI_DEBUG(m_logger, GetName() << " " << __func__
		                              << " Temps "      << wpi::format("%6.3f", time)
		                              << " >= profile " << wpi::format("%6.3f", m_profile[m_phase + 1].m_time));

		// Passer à la prochaine phase du profil.
		++m_phase;
		if (m_phase >= m_profile.size() - 1)
		{
			// Fin de la dernière phase.
			return;
		}

		double const & v_i = m_profile[m_phase + 0].m_speed;  // Vitesse initiale
		double const & v_f = m_profile[m_phase + 1].m_speed;  // Vitesse finale
		double const & t_p = m_profile[m_phase - 1].m_time;   // Temps précédent
		double const & t_i = m_profile[m_phase + 0].m_time;   // Temps initial
		double const & t_f = m_profile[m_phase + 1].m_time;   // Temps final

		WPI_DEBUG(m_logger, GetName() << " " << __func__ << " Vitesse de la phase " << m_phase
		                              << " de "      << wpi::format("%5.2f", v_i)
		                              << " a "       << wpi::format("%5.2f", v_f)
		                              << " pendant " << wpi::format("%6.3f", t_f - t_i) << " sec.");

		// Trouver l'accélération du profil.
		double acceleration = (v_f - v_i) / (t_f - t_i);

		// Utiliser un nouvel object Mrua pour calculer la vitesse et la position en fonction du temps.
		// Note: le temps initial de la nouvelle phase est le temps final la phase précédente.
		double position = m_mrua->getIntegratedPosition(t_i - t_p);
		WPI_DEBUG(m_logger, GetName() << " " << __func__ 
		                              << ", position: "  << wpi::format("%5.2f", position)
		                              << ", speed: "     << wpi::format("%5.2f", v_i));
		m_mrua.reset(new Mrua(acceleration, v_i, position));
		WPI_DEBUG1(m_logger, GetName() << " Mrua: " << *m_mrua);
	}

	// Calculer le temps relatif au début de la (nouvelle) phase du profil en cours.
	double const & t_i = m_profile[m_phase + 0].m_time;
	double time_phase = time - t_i;

	m_speed = m_mrua->getIntegratedSpeed(time_phase);

	// Assigner la consigne en fonction du type de régulateur PID turn.
	WPI_DEBUG2(m_logger, GetName() << " " << __func__ << "m_speed: " << m_speed);
	Robot::m_sysBaseMobile.setRotationRateSP(m_speed);

	// Log à chaque demi-seconde, ou si le logger log.
	if (((time - m_lastTime) > 0.5) ||
		(m_logger.min_level() <= wpi::WPI_LOG_DEBUG4))
	{
		WPI_DEBUG(m_logger, GetName() << " " << __func__ 
		                              << ", m_speed: "   << wpi::format("%5.2f", m_speed));
		m_lastTime = time;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool cmdTournerBaseMobile::IsFinished()
{
	// Vérifier si tout le profil est fini.
	if (m_phase >= m_profile.size() - 1)
	{
		WPI_DEBUG(m_logger, GetName() << " IsFinished!");
		return true;
	}
	return false || IsCanceled();
}

// Called once after isFinished returns true
void cmdTournerBaseMobile::End()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdTournerBaseMobile::Interrupted()
{
	WPI_DEBUG(m_logger, GetName() << " " << __func__ << " Interruption de la commande.");
}


void cmdTournerBaseMobile::setRotation(double rotation)
{
	m_rotation = rotation;
	WPI_DEBUG1(m_logger, GetName() << " " << __func__ << " m_rotation " << m_rotation);
}

void cmdTournerBaseMobile::setRotationSpeedMax(double rotation_speed_max)
{
	m_rotation_speed_max = rotation_speed_max;
}

void cmdTournerBaseMobile::setRotationAcceleration(double rotation_acceleration)
{
	m_rotation_acceleration = rotation_acceleration;
}