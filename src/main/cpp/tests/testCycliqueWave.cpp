/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#define _USE_MATH_DEFINES 

#include "tests/testCycliqueWave.h"

#include <frc/SmartDashboard/SmartDashboard.h>
#include <wpi/Format.h>

#include <cmath>

#include "Logger.h"
#include "Robot.h"


testCycliqueWave::testCycliqueWave()
	 : Command(__func__)
	 , m_amplitude(0.0)
	 , m_offset(0.0)
	 , m_omega(M_PI_4)   // Un cycle par 4 secondes.
	 , m_logger(log_func)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::m_sysBras);

	// Offrir des valeurs par défaut.
	frc::SmartDashboard::PutNumber("kP", m_kP);
	frc::SmartDashboard::PutNumber("kI", m_kI);
	frc::SmartDashboard::PutNumber("kD", m_kD);
	frc::SmartDashboard::PutNumber("kF", m_kF);
	frc::SmartDashboard::PutNumber("Amplitude",  m_amplitude); // radians
	frc::SmartDashboard::PutNumber("Offset",     m_offset);    // radians
	frc::SmartDashboard::PutNumber("Pulsations", m_omega);     // rad/sec

	m_logger.set_min_level(wpi::WPI_LOG_DEBUG1);
}

// Called just before this Command runs the first time
void testCycliqueWave::Initialize()
{
	m_amplitude = frc::SmartDashboard::GetNumber("Amplitude", m_amplitude);
	m_omega     = frc::SmartDashboard::GetNumber("Pulsations", m_omega);
	WPI_INFO(m_logger, GetName() << " " << __func__ << "Amplitude: " << wpi::format("%5.2f", m_amplitude) << ", Pulsations: " << wpi::format("%5.2f", m_omega));

	m_kP = frc::SmartDashboard::GetNumber("kP", 0.0);
	m_kI = frc::SmartDashboard::GetNumber("kI", 0.0);
	m_kD = frc::SmartDashboard::GetNumber("kD", 0.0);
	m_kF = frc::SmartDashboard::GetNumber("kF", 0.0);
	// Position initiale et minimale du bras pendant les cycles.
	m_position = Robot::m_sysBras.getPositionFB();
	Robot::m_sysBras.EnablePID(m_kP, m_kI, m_kD, m_kF);
}

// Called repeatedly when this Command is scheduled to run
void testCycliqueWave::Execute()
{
	double sine = std::sin(m_omega * TimeSinceInitialized());
	if ((std::signbit(m_lastSine) == true) && (std::signbit(sine) == false))
	{
		// Nouveau cycle et 
		// changement de paramètres quand la vitesse est à son mininum.
		double amplitude = frc::SmartDashboard::GetNumber("Amplitude", m_amplitude);
		if (m_amplitude != amplitude)
		{
			WPI_DEBUG1(m_logger, GetName() << " " << __func__ << " Amplitude: " << wpi::format("%5.2f", m_amplitude));
		}
		m_amplitude = amplitude;

		double kP = frc::SmartDashboard::GetNumber("kP", m_kP);
		double kI = frc::SmartDashboard::GetNumber("kI", m_kI);
		double kD = frc::SmartDashboard::GetNumber("kD", m_kD);
		double kF = frc::SmartDashboard::GetNumber("kF", m_kF);
		if ((kP != m_kP) || (kI != m_kI) || (kD != m_kD) || (kF != m_kF))
		{
			m_kP = kP;
			m_kI = kI;
			m_kD = kD;
			m_kF = kF;
			Robot::m_sysBras.DisablePID();   // Est-ce nécessaire ?
			Robot::m_sysBras.EnablePID(m_kP, m_kI, m_kD, m_kF);
			WPI_DEBUG(m_logger, "Changer le regulateur, constantes: "
			               <<   "P " << wpi::format("%5.2f", m_kP)
			               << ", I " << wpi::format("%5.2f", m_kI)
			               << ", D " << wpi::format("%5.2f", m_kD)
			               << ", F " << wpi::format("%5.2f", m_kF));
		}
	}
	m_lastSine = sine;

	// Varier la position du bras entre sa position initiale et une position initiale + 2·amplitude.
	m_offset = frc::SmartDashboard::GetNumber("Offset", m_offset);
	double position = m_position + m_offset - m_amplitude + m_amplitude*std::cos(m_omega * TimeSinceInitialized());;
	Robot::m_sysBras.setPositionSP(position);
	WPI_DEBUG2(m_logger, GetName() << " " << __func__ << " Position: " << wpi::format("%6.3f", position));
}

// Make this return true when this Command no longer needs to run execute()
bool testCycliqueWave::IsFinished()
{
	// La commande sera interrompue.
	return false;
}

// Called once after isFinished returns true
void testCycliqueWave::End()
{
	WPI_DEBUG1(m_logger, GetName() << " " << __func__);
	Robot::m_sysBras.DisablePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void testCycliqueWave::Interrupted()
{
	WPI_WARNING(m_logger, GetName() << " " << __func__);
	Robot::m_sysBras.DisablePID();
}
