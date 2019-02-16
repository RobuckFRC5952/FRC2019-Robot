/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "commands/DescendBras.h"
#include "commands/MonteBras.h"
#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>
#include "commands/LancerBallon.h"
#include "commands/AttrapperBallon.h"

/// \file OI.h
/// \brief Interface de l'opérateur.
using namespace frc;

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>
#include "commands/AvancerCrochet.h"
using namespace frc;
class OI
{
 public:
	OI();
	/// Le joystick.
	Joystick m_joystick;
private:

	/// Les boutons
	JoystickButton *m_boutonMonteBras;
	JoystickButton *m_boutonBaisserBras;
	JoystickButton *m_boutonLancerBallon;
	JoystickButton *m_bouton_Attrapper_la_hatch;
	JoystickButton *m_boutonAttrapperBallon;

	/// Commande Ã  appliquer quand les bouton sont enfoncÃ©.
	MonteBras m_MonteBras;
	DescendBras m_DescendBras;
	cmdLancerBallon m_LancerBallon;
	AvancerCrochet m_AvancerCrochet;
	AttrapperBallon m_AttraperBallon;
};
