/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BaseMobile.h"

sysBaseMobile::sysBaseMobile()
	 : Subsystem(__func__)
{
	const int    pulses_tour  = 2048;            // pulses/tour
	const double pouces_metre =    1.0 / 0.0254; // pouces/mÃ¨tre.  Voir https://en.wikipedia.org/wiki/Conversion_of_units#Length
	const double radius = 3.0 / pouces_metre;

	// Convertir en metres des encodeurs de 360 ticks/tours avec roues de 6 pouces
	m_DriveBaseMoteurDroitEncoder.SetDistancePerPulse( (2.0 * M_PI * radius) / pulses_tour);
	m_DriveBaseMoteurDroitEncoder.SetName("EncD");
	m_DriveBaseMoteurGaucheEncoder.SetDistancePerPulse((2.0 * M_PI * radius) / pulses_tour);
	m_DriveBaseMoteurGaucheEncoder.SetName("EncG");

	AddChild("Moteur droit", m_DriveBaseMoteurDroit);
	AddChild("Moteur gauche", m_DriveBaseMoteurGauche);
	AddChild("Encodeur droit",  m_DriveBaseMoteurDroitEncoder);
	AddChild("Encodeur gauche", m_DriveBaseMoteurGaucheEncoder);
	AddChild("Drive", m_robotDrive);




}

void sysBaseMobile::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
