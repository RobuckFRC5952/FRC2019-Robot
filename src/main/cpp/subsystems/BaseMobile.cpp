/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BaseMobile.h"

#include <array>

#include <frc/SmartDashboard/SmartDashboard.h>


sysBaseMobile::sysBaseMobile()
	 : Subsystem(__func__)
{
	const int    pulses_tour  = 2048;            // pulses/tour
	const double pouces_metre =    1.0 / 0.0254; // pouces/mètre.  Voir https://en.wikipedia.org/wiki/Conversion_of_units#Length
	const double radius       =    3.0 / pouces_metre;

	// Convertir en mètres des encodeurs de 2048 ticks/tours avec roues de 6 pouces.
	m_DriveBaseMoteurDroitEncoder.SetDistancePerPulse( (2.0 * M_PI * radius) / pulses_tour);
	m_DriveBaseMoteurDroitEncoder.SetName("EncD");
	m_DriveBaseMoteurGaucheEncoder.SetDistancePerPulse((2.0 * M_PI * radius) / pulses_tour);
	m_DriveBaseMoteurGaucheEncoder.SetName("EncG");

	m_DriveBaseMoteurDroitEncoder.SetName("MotD");
	m_DriveBaseMoteurGaucheEncoder.SetName("MotG");

	AddChild("MotD",  m_DriveBaseMoteurDroit);
	AddChild("MotG",  m_DriveBaseMoteurGauche);
	AddChild("EncD",  m_DriveBaseMoteurDroitEncoder);
	AddChild("EncG",  m_DriveBaseMoteurGaucheEncoder);
	AddChild("Drive", m_Drive);
}

void sysBaseMobile::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void sysBaseMobile::ArcadeDrive(double xSpeed, double zRotation)
{
	m_Drive.ArcadeDrive(xSpeed, zRotation);
}

void sysBaseMobile::PutSmartDashboard()
{
	std::array<frc::Encoder const *, 2> encoders = {&m_DriveBaseMoteurGaucheEncoder, &m_DriveBaseMoteurDroitEncoder};
	for (frc::Encoder const * encoder : encoders)
	{
		frc::SmartDashboard::PutNumber(encoder->GetName()  + "_Count",     encoder->Get());
		frc::SmartDashboard::PutNumber(encoder->GetName()  + "_Raw",       encoder->GetRaw());
		frc::SmartDashboard::PutNumber(encoder->GetName()  + "_Distance",  encoder->GetDistance());
		// frc::SmartDashboard::PutNumber(encoder->GetName()  + "_Period",    encoder->GetPeriod());
		frc::SmartDashboard::PutNumber(encoder->GetName()  + "_Rate",      encoder->GetRate());
		frc::SmartDashboard::PutBoolean(encoder->GetName() + "_Direction", encoder->GetDirection());
		frc::SmartDashboard::PutBoolean(encoder->GetName() + "_Stopped",   encoder->GetStopped());
	}
}
