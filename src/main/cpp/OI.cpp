/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "RobotMap.h"

//#include <frc/WPILib.h>

#include "RobotMap.h"

OI::OI()
: m_joystick(kJoystickPort)
{
	// Process operator interface input here.
	m_boutonBaisserBras = new JoystickButton(&m_joystick, kJoystickBaisser_bras);
	m_boutonMonteBras = new JoystickButton(&m_joystick, kJoystickMonter_bras);
	m_boutonLancerBallon = new JoystickButton(&m_joystick, kJoystickpousser_ballon);
	m_boutonAttrapperBallon = new JoystickButton(&m_joystick, kJoystickattrapper_ballon);
	m_boutonBaisserBras->WhileHeld(&m_DescendBras);
	m_boutonMonteBras->WhileHeld(&m_MonteBras);
	m_boutonLancerBallon->WhileHeld(&m_LancerBallon);
	m_boutonAttrapperBallon->WhileHeld(&m_AttraperBallon);
}
