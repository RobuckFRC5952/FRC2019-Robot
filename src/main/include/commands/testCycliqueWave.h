/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <wpi/Logger.h>

class testCycliqueWave : public frc::Command
{
 public:
	testCycliqueWave();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

 private:

	/// @name Variables pour l'équation du Signal sinusoïdal
	///@{
	double m_amplitude; // Amplitude de la grandeur (radian)
	double m_omega;     // Pulsation de la grandeur (rad/sec)
	///@}

	/// @name Variables pour le régulateur.
	///@{
	double m_kP = 0.0;
	double m_kI = 0.0;
	double m_kD = 0.0;
	double m_kF = 0.0;
	///@}

	double m_position;
	double m_offset;

	double m_lastSine;

	/// Logger du sous-système.
	wpi::Logger m_logger;
};
