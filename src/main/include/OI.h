/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file OI.h
/// \brief Interface de l'opérateur.

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>


class OI
{
 public:
	OI();

	/// Le joystick.
	frc::Joystick m_joystick;

	/// Ajout des boutons.
	frc::JoystickButton m_button_attrapebal;
	frc::JoystickButton m_button_Lancerbal;
	frc::JoystickButton m_button_Attraper_hatch;
	frc::JoystickButton m_button_Lacher_hatch;
	frc::JoystickButton m_button_DeployerRampe;
	frc::JoystickButton m_button_MonterRampe;
};
