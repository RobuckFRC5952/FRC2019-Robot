/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"
#include "RobotMap.h"
#include "subsystems/Bras.h"
#include "tests/testDeplaceBaseMobile.h"


OI::OI()
: m_joystick(kJoystickPort)
, m_BaisserBras(Robot::m_sysBras.getPositionMin())
, m_MonterBras(Robot::m_sysBras.getPositionMax())
, m_ArreterBras()
{
	// Process operator interface input here.
	m_boutonInverseDirection    = new frc::JoystickButton(&m_joystick, kJoystickInvDir);

	m_boutonBaisserBras         = new frc::JoystickButton(&m_joystick, kJoystickBaisser_bras);
	m_boutonMonterBras          = new frc::JoystickButton(&m_joystick, kJoystickMonter_bras);

	m_boutonLancerBallon        = new frc::JoystickButton(&m_joystick, kJoystickpousser_ballon);
	m_boutonAttrapperBallon     = new frc::JoystickButton(&m_joystick, kJoystickattrapper_ballon);

	m_bouton_Attrapper_la_hatch = new frc::JoystickButton(&m_joystick, kJoystickattrapper_la_hatch);
	m_bouton_Pousser_la_hatch   = new frc::JoystickButton(&m_joystick, kJoystickpousser_la_hatch);

	m_boutonDeployerRampe       = new frc::JoystickButton(&m_joystick, kJoystickDeployer_la_rampe);
	m_boutonRemonterRampe       = new frc::JoystickButton(&m_joystick, kJoystickRemonter_la_rampe);

	m_boutonInverseDirection->WhenPressed(&m_InverseDirection);

	m_boutonBaisserBras->WhenPressed(&m_BaisserBras);
	m_boutonBaisserBras->WhenReleased(&m_ArreterBras);

	m_boutonMonterBras->WhenPressed(&m_MonterBras);
	m_boutonMonterBras->WhenReleased(&m_ArreterBras);

	m_boutonLancerBallon->WhileHeld(&m_LancerBallon);
	m_boutonAttrapperBallon->WhileHeld(&m_AttraperBallon);

	m_bouton_Attrapper_la_hatch->WhileHeld(&m_AvancerCrochet);
	m_bouton_Pousser_la_hatch->WhileHeld(&m_RetracterCrochet);

	m_boutonDeployerRampe->WhileHeld(&m_DeployerRampe);
	m_boutonRemonterRampe->WhileHeld(&m_RemonterRampe);

	testDeplaceBaseMobile * cmd = new testDeplaceBaseMobile();
	frc::SmartDashboard::PutData("DeplaceMoteur", cmd);
}
