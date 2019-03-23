/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Buttons/JoystickButton.h>
#include <frc/Joystick.h>

#include "commands/InverserDirection.h"
#include "commands/DeplacerBras.h"
#include "commands/ArreterBras.h"
#include "commands/LancerBallon.h"
#include "commands/AttrapperBallon.h"
#include "commands/AvancerCrochet.h"
#include "commands/RetracterCrochet.h"
#include "commands/DeployerRampe.h"

#include "tests/testCycliqueWave.h"


class OI
{
 public:
	OI();
	/// Le joystick.
	frc::Joystick m_joystick;
private:

	/// Les boutons.
	frc::JoystickButton *m_boutonInverseDirection;

	frc::JoystickButton *m_boutonMonterBras;
	frc::JoystickButton *m_boutonBaisserBras;

	frc::JoystickButton *m_boutonLancerBallon;
	frc::JoystickButton *m_boutonAttrapperBallon;

	frc::JoystickButton *m_bouton_Attrapper_la_hatch;
	frc::JoystickButton *m_bouton_Pousser_la_hatch;

	frc::JoystickButton *m_boutonDeployerRampe;
	frc::JoystickButton *m_boutonRemonterRampe;

	frc::JoystickButton *m_bouton_trigger;

	/// Commande à appliquer quand les boutons sont enfoncés.

	InverserDirection m_InverseDirection;

	cmdDeplacerBras m_BaisserBras;
	cmdDeplacerBras m_MonterBras;
	cmdArreterBras m_ArreterBras;

	cmdLancerBallon m_LancerBallon;
	AttrapperBallon m_AttraperBallon;
	AvancerCrochet m_AvancerCrochet;
	RetracterCrochet m_RetracterCrochet;
	DeployerRampe m_DeployerRampe {-0.2};
	DeployerRampe m_RemonterRampe { 0.8};
	
	testCycliqueWave m_testCycliqueWave;
};
