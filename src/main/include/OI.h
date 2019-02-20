/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>

#include "commands/MonteBras.h"
#include "commands/DescendBras.h"
#include "commands/LancerBallon.h"
#include "commands/AttrapperBallon.h"
#include "commands/AvancerCrochet.h"
#include "commands/RetracterCrochet.h"
#include "commands/DeployerRampe.h"


using namespace frc;
class OI
{
 public:
	OI();
	/// Le joystick.
	Joystick m_joystick;
private:

	/// Les boutons.
	JoystickButton *m_boutonMonteBras;
	JoystickButton *m_boutonBaisserBras;

	JoystickButton *m_boutonLancerBallon;
	JoystickButton *m_boutonAttrapperBallon;

	JoystickButton *m_bouton_Attrapper_la_hatch;
	JoystickButton *m_bouton_Pousser_la_hatch;

	JoystickButton *m_boutonDeployerRampe;
	JoystickButton *m_boutonRemonterRampe;

	/// Commande à appliquer quand les boutons sont enfoncés.
	MonteBras m_MonteBras;
	DescendBras m_DescendBras;
	cmdLancerBallon m_LancerBallon;
	AttrapperBallon m_AttraperBallon;
	AvancerCrochet m_AvancerCrochet;
	RetracterCrochet m_RetracterCrochet;
	DeployerRampe m_DeployerRampe {-0.2};
	DeployerRampe m_RemonterRampe { 0.8};
};
