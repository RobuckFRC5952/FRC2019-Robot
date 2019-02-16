/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "RobotMap.h"


OI::OI()
//Les bouttons du joystick 3D Pro.
: m_joystick(kJoystickPort)
, m_button_attrapebal(&m_joystick, kJoystickattrapper_ballon)
, m_button_Lancerbal(&m_joystick, kJoystickpousser_ballon)
, m_button_Attraper_hatch(&m_joystick, kJoystickattrapper_la_hatch)
, m_button_Lacher_hatch(&m_joystick, kJoystickpousser_la_hatch)
, m_button_DeployerRampe(&m_joystick, kJoystickDeployer_la_rampe)
, m_button_MonterRampe(&m_joystick, kJoystickRemonter_la_rampe)
, m_DeployerRampe(0.1)
{
	//Associer le boutton de deployer_rampe à la commande m_button_DeployerRampe
	m_button_DeployerRampe.WhileHeld(&m_DeployerRampe);
}
