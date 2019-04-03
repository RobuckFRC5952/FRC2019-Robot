/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tests/testTourneBaseMobile.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/Format.h>

#include "Robot.h"
#include "subsystems/BaseMobile.h"


char const * testTourneBaseMobile::m_key_rotation = "rotation";
char const * testTourneBaseMobile::m_key_rotation_speed_max = "rotation_speed_max";
char const * testTourneBaseMobile::m_key_rotation_acceleration = "rotation_accel";

char const * testTourneBaseMobile::m_key_kP = "turn_kP";
char const * testTourneBaseMobile::m_key_kI = "turn_kI";
char const * testTourneBaseMobile::m_key_kD = "turn_kD";
char const * testTourneBaseMobile::m_key_kF = "turn_kF";


testTourneBaseMobile::testTourneBaseMobile()
: cmdTournerBaseMobile(0.0)
, m_rotation(0.0)
, m_rotation_speed_max(1.0)
, m_rotation_acceleration(1.0)
{
	// Renommer la commande cmdDeplaceMoteur par cmdTestDeplaceMoteur.
	SetName(__func__);

	frc::SmartDashboard::PutNumber(m_key_rotation, 0.0);
	frc::SmartDashboard::PutNumber(m_key_rotation_speed_max, 0.0);
	frc::SmartDashboard::PutNumber(m_key_rotation_acceleration, 0.0);

	frc::SmartDashboard::PutNumber(m_key_kP, 0.0);
	frc::SmartDashboard::PutNumber(m_key_kI, 0.0);
	frc::SmartDashboard::PutNumber(m_key_kD, 0.0);
	frc::SmartDashboard::PutNumber(m_key_kF, 0.0);

	// Ajuster le niveau de messages à la Console.
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}

// Called just before this Command runs the first time
void testTourneBaseMobile::Initialize()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);

	m_rotation              = frc::SmartDashboard::GetNumber(m_key_rotation,              0.0);
	m_rotation_speed_max    = frc::SmartDashboard::GetNumber(m_key_rotation_speed_max,    m_rotation_speed_max);
	m_rotation_acceleration = frc::SmartDashboard::GetNumber(m_key_rotation_acceleration, m_rotation_acceleration);
	setRotation(m_rotation);
	setRotationSpeedMax(m_rotation_speed_max);
	setRotationAcceleration(m_rotation_acceleration);

	WPI_DEBUG(m_logger, "distance "     << wpi::format("%5.2f", m_rotation)
	                <<  ", speed max: " << wpi::format("%5.2f", m_rotation_speed_max)
	                <<  ", accel: "     << wpi::format("%5.2f", m_rotation_acceleration));

	double kP = frc::SmartDashboard::GetNumber(m_key_kP, 0.0);
	double kI = frc::SmartDashboard::GetNumber(m_key_kI, 0.0);
	double kD = frc::SmartDashboard::GetNumber(m_key_kD, 0.0);
	double kF = frc::SmartDashboard::GetNumber(m_key_kF, 0.0);
	Robot::m_sysBaseMobile.EnableTurnPID(kP, kI, kD, kF);

	cmdTournerBaseMobile::Initialize();
}

// Called repeatedly when this Command is scheduled to run
void testTourneBaseMobile::Execute()
{
	cmdTournerBaseMobile::Execute();
}

// Make this return true when this Command no longer needs to run execute()
bool testTourneBaseMobile::IsFinished()
{
	return cmdTournerBaseMobile::IsFinished();
}

// Called once after isFinished returns true
void testTourneBaseMobile::End()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	Robot::m_sysBaseMobile.DisablePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void testTourneBaseMobile::Interrupted()
{
	WPI_INFO(m_logger, GetName() << " " << __func__);
	Robot::m_sysBaseMobile.DisablePID();
}
