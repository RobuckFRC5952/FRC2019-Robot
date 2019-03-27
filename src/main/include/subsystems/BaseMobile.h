/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file BaseMobile.h
/// \brief Sous-système représentant la base mobile avec les quatre moteurs et encodeurs.

#include <frc/commands/Subsystem.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Encoder.h>
#include <frc/VictorSP.h>
#include <wpi/Logger.h>

#include "RobotMap.h"

enum class eDirection
{
	Bras,
	Crochet,
};

class sysBaseMobile : public frc::Subsystem
{
 private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	/// @name Les encodeurs sur les gearbox.
	/// @{
	frc::Encoder m_DriveBaseMoteurDroitEncoder  {kBaseMobileEncoderD_DioChannelA, kBaseMobileEncoderD_DioChannelB, true,  frc::Encoder::k4X};
	frc::Encoder m_DriveBaseMoteurGaucheEncoder {kBaseMobileEncoderG_DioChannelA, kBaseMobileEncoderG_DioChannelB, false, frc::Encoder::k4X};
	/// @}

	/// @name Les contrôleurs de moteurs sont quatre VEX PRO Victor SP (P/N: 217-9090).
	/// @{
	frc::VictorSP m_DriveBaseMoteurDroit  {kBaseMobileMoteursD_PwmChannel};
	frc::VictorSP m_DriveBaseMoteurGauche {kBaseMobileMoteursG_PwmChannel};
	/// @}

	frc::DifferentialDrive m_Drive {m_DriveBaseMoteurDroit, m_DriveBaseMoteurGauche};

	eDirection m_direction {eDirection::Bras};

	/// Logger du sous-système.
	wpi::Logger m_logger;

	/** \name Variables pour comparer avec les nouvelles valeurs, de vitesse, de rotation, etc.
	 *
	 * Ceci permet d'afficher un message à la console que quand il y a changement.
	 */
	/// @{
	double m_lastXSpeed = 0.0;
	double m_lastZRotation = 0.0;
	/// @}


 public:
	sysBaseMobile();
	void InitDefaultCommand() override;

	void ArcadeDrive(double xSpeed, double zRotation);

	void setDirection(eDirection direction);

	void PutSmartDashboard();
};
