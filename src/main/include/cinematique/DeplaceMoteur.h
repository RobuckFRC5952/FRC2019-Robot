/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file DeplaceMoteur.h
/// \brief Commande pour faire tourner le moteur d'une distance désirée.

#include <limits>
#include <vector>

#include <frc/commands/Command.h>
#include <frc/PIDSource.h>
#include <wpi/Logger.h>

#include "cinematique/Cinematique.h"

class Mrua;
class ISubsystem;


/** Commande pour faire tourner le moteur d'une distance désirée en suivant un
 *  profil de vitesse.
 *
 * \sa Voir aussi la classe Deplacement qui génère ce profil.
 */
class cmdDeplaceMoteur : public frc::Command
{
 public:
	cmdDeplaceMoteur(ISubsystem & subsystem, double distance, double speed_max, double acceleration = std::numeric_limits<double>::infinity());
	virtual void Initialize() override;
	virtual void Execute() override;
	virtual bool IsFinished() override;
	virtual void End() override;
	virtual void Interrupted() override;

	/// \name Setters
	/// @{

	/// Changer la distance à parcourir avant l'initialisation.
	void setDistance(double distance);

	void setSpeedMax(double speed_max);

	void setAcceleration(double acceleration);
	/// @}

 private:

	/// La référence du sous-system contrôlé par cette commande.
	ISubsystem & m_subsystem;

	frc::PIDSourceType m_source_type;

	/// La distance relative à parcourir.
	double m_distance;

	/// Vitesse maximale du moteur.
	double m_speed_max;

	/// La valeur de l'accélération.
	double m_acceleration;

	/// Le profil de vitesse pour parcourir la distance.
	std::vector<Vt> m_profile;

	/// Les différentes phases du profil de vitesse.
	std::size_t m_phase;

	/// Objet de type Mrua réalloué en mémoire à chaque fois que la vitesse désirée est changée.
	std::unique_ptr<Mrua> m_mrua;

	// Position actuelle commandée.
	double m_position;

	// Vitesse actuelle commandée.
	double m_speed;

 protected:

	/// Logger du sous-système.
	wpi::Logger m_logger;

 private:

	/// \name Variables pour comparer avec les nouvelles valeurs, etc.
	/// @{
	double m_lastTime;
	/// @}
};
