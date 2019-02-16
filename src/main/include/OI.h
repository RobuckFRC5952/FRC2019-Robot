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
#include "commands/AvancerCrochet.h"
using namespace frc;
class OI
{
 public:
	OI();

	/// Le joystick.
	frc::Joystick m_joystick;

	JoystickButton *m_bouton_Attrapper_la_hatch;
	AvancerCrochet m_AvancerCrochet;
};

