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
#include <frc/Encoder.h>
#include <frc/VictorSP.h>

#include "RobotMap.h"


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
 public:
	sysBaseMobile();
	void InitDefaultCommand() override;
};
