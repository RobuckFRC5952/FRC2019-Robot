/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "cinematique/DeplaceMoteur.h"

#include <wpi/Format.h>

#include "cinematique/Deplacement.h"
#include "cinematique/Mrua.h"
#include "Logger.h"
#include "subsystems/ISubsystem.h"


cmdDeplaceMoteur::cmdDeplaceMoteur(ISubsystem & subsystem, double distance, double speed_max, double acceleration)
	: Command(__func__)
	, m_subsystem(subsystem)
	, m_distance(distance)
	, m_speed_max(speed_max)
	, m_acceleration(acceleration)
	, m_phase(0)
	, m_position(0.0)
	, m_logger(log_func)
	, m_lastTime(0.0)
{
	WPI_DEBUG3(m_logger, __PRETTY_FUNCTION__);
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void cmdDeplaceMoteur::Initialize()
{
	WPI_INFO(m_logger, GetName() << " Distance " << wpi::format("%5.2f", m_distance));
	if (std::abs(m_distance) <= 0.0)  // TODO 
	{
		WPI_WARNING(m_logger, GetName() << " Distance trop petite.");
		Cancel();
		return;
	}

	// Trouver le profil de vitesse.
	Deplacement d;
	double initial_speed = 0.0;   // FIXME Initial and final speed.
	double final_speed   = 0.0;   // On assume qu'un déplacement de moteur se fait toujours à l'arrêt.

	// L'object de type Deplacement peut lancer des exceptions de type: std::exception.
	// Il faut les attrapper sinon l'application se termine automatiquement (et brutalement).
	try
	{
		d.setSpeedMax(m_speed_max);
		d.setAcceleration(m_acceleration);
		m_profile = d.getSpeedProfile(m_distance, initial_speed, final_speed);
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

	// Trouver la position actuelle du sous-système.
	m_position = m_subsystem.getPositionFB();

	// Trouver le signe de l'accélération. Il est en fonction de la vitesse 
	// désirée par rapport à la vitesse actuelle.
	double acceleration = std::copysign(m_acceleration, v1 - v0);

	// Utiliser un nouvel object Mrua pour calculer la vitesse et la position en fonction du temps.
	m_mrua.reset(new Mrua(acceleration, v0, m_position));
	WPI_DEBUG1(m_logger, GetName() << " Mrua: " << *m_mrua);

	m_lastTime = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void cmdDeplaceMoteur::Execute()
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
		                              << " m_position: " << wpi::format("%5.2f", m_position)
		                              << ", position: "  << wpi::format("%5.2f", position)
		                              << ", speed: "     << wpi::format("%5.2f", v_i));
		m_mrua.reset(new Mrua(acceleration, v_i, position));
		WPI_DEBUG1(m_logger, GetName() << " Mrua: " << *m_mrua);
	}

	// Calculer le temps relatif au début de la (nouvelle) phase du profil en cours.
	double const & t_i = m_profile[m_phase + 0].m_time;
	double time_phase = time - t_i;
	double position = m_mrua->getIntegratedPosition(time_phase);

	// Restreindre la position par les limites du sous-système.
	// m_position = std::max(m_subsystem.getPositionMin(), std::min(position, m_subsystem.getPositionMax()));
	m_position = position; // TEMP

	// TODO if GetPIDSourceType() == frc::PIDSourceType::kDisplacement...
	m_subsystem.setPositionSP(m_position);

	// Log à chaque demi-seconde, ou si le logger log.
	if (((time - m_lastTime) > 0.5) ||
		(m_logger.min_level() <= wpi::WPI_LOG_DEBUG4))
	{
		double speed = m_mrua->getIntegratedSpeed(time_phase);
		WPI_DEBUG(m_logger, GetName() << " " << __func__ 
		                              << " m_position: " << wpi::format("%5.2f", m_position)
		                              << ", speed: "     << wpi::format("%5.2f", speed));
		m_lastTime = time;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool cmdDeplaceMoteur::IsFinished()
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
void cmdDeplaceMoteur::End()
{
	WPI_DEBUG3(m_logger, GetName() << " " << __func__);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdDeplaceMoteur::Interrupted()
{
	WPI_DEBUG(m_logger, GetName() << " " << __func__ << " Interruption de la commande.");
}


void cmdDeplaceMoteur::setDistance(double distance)
{
	m_distance = distance;
	WPI_DEBUG1(m_logger, GetName() << " " << __func__ << " m_distance " << m_distance);
}
