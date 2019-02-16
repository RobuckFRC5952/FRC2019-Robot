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
{
	// Process operator interface input here.
	m_bouton_Attrapper_la_hatch = new JoystickButton(&m_joystick, kJoystickattrapper_la_hatch);
	m_bouton_Attrapper_la_hatch->WhileHeld(&m_AvancerCrochet);
}
