/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BaseMobile.h"

#include <array>
#include <cmath>

#include <frc/SmartDashboard/SmartDashboard.h>
#include <wpi/Format.h>


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

	WPI_INFO(m_logger, "Moteur droit sur le canal PWM  " << m_DriveBaseMoteurDroit.GetChannel()
	                << " avec encodeur sur les canaux DIO " << kBaseMobileEncoderD_DioChannelA << " et " << kBaseMobileEncoderD_DioChannelB << ".");
	WPI_INFO(m_logger, "Moteur gauche sur le canal PWM " << m_DriveBaseMoteurGauche.GetChannel()
	                << " avec encodeur sur les canaux DIO " << kBaseMobileEncoderG_DioChannelA << " et " << kBaseMobileEncoderG_DioChannelB << ".");
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

	// Afficher à la console seulement si une des valeurs changent de 5% par rapport à la dernière.
	// Un message imprimé à chaque 20 ms est trop verbeux.
	if ((std::fabs((xSpeed - m_lastXSpeed)/m_lastXSpeed) > 0.05) || (std::fabs((zRotation - m_lastZRotation)/m_lastZRotation) > 0.05))
	{
		WPI_DEBUG2(m_logger, "xSpeed:" << wpi::format("%5.2f", xSpeed) 
		                  << "zRotation:" << wpi::format("%5.2f", zRotation)
		                  << "Distances [EncD, EncG]: " << wpi::format("%5.2f", m_DriveBaseMoteurDroitEncoder.GetDistance()) << " " << wpi::format("%5.2f", m_DriveBaseMoteurGaucheEncoder.GetDistance())
		                  << "Rates     [EncD, EncG]: " << wpi::format("%5.2f", m_DriveBaseMoteurDroitEncoder.GetRate())     << " " << wpi::format("%5.2f", m_DriveBaseMoteurGaucheEncoder.GetRate()));

		// Enregistrer la vitesse courrant pour la comparer la prochaine fois qu'on exécute
		// cette méthode avec une nouvelle valeur de 'speed'.
		m_lastXSpeed    = xSpeed;
		m_lastZRotation = zRotation;
	}
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
