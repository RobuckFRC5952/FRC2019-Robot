/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>

#include "commands/InverserDirection.h"
#include "commands/MonteBras.h"
#include "commands/DescendBras.h"
#include "commands/LancerBallon.h"
#include "commands/AttrapperBallon.h"
#include "commands/AvancerCrochet.h"
#include "commands/RetracterCrochet.h"
#include "commands/DeployerRampe.h"

namespace frc
{
	class JoystickButton;
}


class OI
{
 public:
	OI();
	/// Le joystick.
	frc::Joystick m_joystick;

private:
	/// \name Les boutons.
	/// @{
	frc::JoystickButton *m_boutonInverseDirection;

	frc::JoystickButton *m_boutonMonterBras;
	frc::JoystickButton *m_boutonBaisserBras;

	frc::JoystickButton *m_boutonLancerBallon;
	frc::JoystickButton *m_boutonAttrapperBallon;

	frc::JoystickButton *m_bouton_Attrapper_la_hatch;
	frc::JoystickButton *m_bouton_Pousser_la_hatch;

	frc::JoystickButton *m_boutonDeployerRampe;
	frc::JoystickButton *m_boutonRemonterRampe;
	/// @}

	/// \name Commandes à appliquer quand les boutons sont stimulés.
	/// @{
	InverserDirection m_InverseDirection;

	MonteBras m_MonteBras;
	DescendBras m_DescendBras;

	cmdLancerBallon m_LancerBallon;
	AttrapperBallon m_AttraperBallon;

	AvancerCrochet m_AvancerCrochet;
	RetracterCrochet m_RetracterCrochet;

	DeployerRampe m_DeployerRampe {-0.4};
	DeployerRampe m_RemonterRampe { 0.8};
	/// @}
};
