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

class OI
{
 public:
	OI();

	/// Le joystick.
	frc::Joystick m_joystick;
};
private:
	/// Le joystick.
	frc::Joystick m_joystick;

	/// Le bouton \e Monter_bras et Baisser_bras.
	frc::JoystickButton m_button11;
	frc::JoystickButton m_button10;


	/// Commande Ã  appliquer quand le bouton \e Trigger est enfoncÃ©.
	cmdJoystickCtrlSpeed m_cmdJoystickCtrlSpeed;
