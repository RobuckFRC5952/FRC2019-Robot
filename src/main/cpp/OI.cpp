/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

//#include <frc/WPILib.h>

#include "RobotMap.h"

OI::OI()
: m_joystick(kJoystickPort)
, m_button_attrapebal (&m_joystick, kJoystickATK3attrapper_ballon)
, m_button_Lancerbal (&m_joystick, kJoystickATK3pousser_ballon)
, m_button_Attraper_hatch (&m_joystick, kJoystickATK3attrapper_la_hatch)
, m_button_Lacher_hatch (&m_joystick, kJoystickATK3pousser_la_hatch)
, m_button_DeployerRampe (&m_joystick, kJoystickATK3deployer_rampe)
, m_button_MonterRampe (&m_joystick, kJoystickATK3Remonter_rampe)
{
	// Process operator interface input here.
}
