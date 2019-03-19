/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>

#include <frc/commands/Command.h>
#include <wpi/Logger.h>

#include "cinematique/Mrua.h"


class cmdArreterBras : public frc::Command
{
 public:
	cmdArreterBras();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

 private:

	void setSpeedSP(double speed_sp);

	/// Accélération du moteur (rad/sec²).
	double m_acceleration;

	/// Vitesse du moteur (rad/sec).
	double m_speed;

	/// Position du moteur (rad).
	double m_position;

	/// Vitesse désirée du moteur (rad/sec).
	double m_speed_sp;

	/// Objet de type Mrua réalloué en mémoire à chaque fois que la vitesse désirée est changée.
	std::unique_ptr<Mrua> m_mrua;

	/// Logger du sous-système.
	wpi::Logger m_logger;

	/** \name Variables pour comparer avec leurs nouvelles valeurs.
	 *
	 * Ceci permet d'afficher un message à la console que quand il y a changement.
	 */
	/// @{
	double m_lastTime;
	/// @}
};
