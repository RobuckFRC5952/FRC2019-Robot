/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <wpi/Logger.h>

#include "cinematique/Cinematique.h"


class Mrua;

class cmdTournerBaseMobile : public frc::Command
{
 public:
	cmdTournerBaseMobile(double rotation);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	/// Changer la distance à parcourir avant l'initialisation.
	void setRotation(double rotation);

	void setRotationSpeedMax(double rotation_speed_max);

	void setRotationAcceleration(double rotation_acceleration);

 private:
	double m_rotation;

	double m_rotation_speed_max;

	double m_rotation_acceleration;

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
	/// Logger de la commande.
	wpi::Logger m_logger;

 private:

	/// \name Variables pour comparer avec les nouvelles valeurs, etc.
	/// @{
	double m_lastTime;
	/// @}
};
