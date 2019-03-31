/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#define _USE_MATH_DEFINES 

#include "subsystems/BaseMobile.h"

#include <array>
#include <cmath>
#include <stdexcept>
#include <limits>

#include <frc/SmartDashboard/SmartDashboard.h>
#include <wpi/Format.h>

#include "Logger.h"


// Limites physique du sous-système.
double sysBaseMobile::speedMax =  1.5; // metre/sec 	TODO TBD
double sysBaseMobile::accelMax =  2.0; // metre/sec²	TODO TBD

sysBaseMobile::sysBaseMobile()
	: Subsystem(__func__)
	, m_DriveBaseMoteurDroitEncoder( kBaseMobileEncoderD_DioChannelA, kBaseMobileEncoderD_DioChannelB, true)
	, m_DriveBaseMoteurGaucheEncoder(kBaseMobileEncoderG_DioChannelA, kBaseMobileEncoderG_DioChannelB, false)
	, m_DriveBaseMoteurDroit( kBaseMobileMoteursD_PwmChannel)
	, m_DriveBaseMoteurGauche(kBaseMobileMoteursG_PwmChannel)
	, m_Drive(m_DriveBaseMoteurDroit, m_DriveBaseMoteurGauche)
	, m_direction(eDirection::Bras)
	, m_speed_sp(0.0)
	, m_rotation_rate_sp(0.0)
	, m_pidSrcEncAvg(m_DriveBaseMoteurGaucheEncoder, m_DriveBaseMoteurDroitEncoder)
	, m_pidController(0.0, 0.0, 0.0, m_pidSrcEncAvg, m_pidOutput)
	, m_pidOutput(this)
	, m_logger(log_func)
{
	const int    pulses_tour  = 2048;            // pulses/tour
	const double pouces_metre =    1.0 / 0.0254; // pouces/mètre.  Voir https://en.wikipedia.org/wiki/Conversion_of_units#Length
	const double radius       =    3.0 / pouces_metre;

	m_DriveBaseMoteurDroit.SetInverted(true);

	// Convertir en mètres des encodeurs de 2048 ticks/tours avec roues de 6 pouces.
	m_DriveBaseMoteurDroitEncoder.SetDistancePerPulse( (2.0 * M_PI * radius) / pulses_tour);
	m_DriveBaseMoteurDroitEncoder.SetName("EncD");
	m_DriveBaseMoteurGaucheEncoder.SetDistancePerPulse((2.0 * M_PI * radius) / pulses_tour);
	m_DriveBaseMoteurGaucheEncoder.SetName("EncG");

	m_DriveBaseMoteurDroit.SetName("MotD");
	m_DriveBaseMoteurGauche.SetName("MotG");

	m_pidSrcEncAvg.SetPIDSourceType(frc::PIDSourceType::kRate);

	AddChild("MotD",       m_DriveBaseMoteurDroit);
	AddChild("MotG",       m_DriveBaseMoteurGauche);
	AddChild("EncD",       m_DriveBaseMoteurDroitEncoder);
	AddChild("EncG",       m_DriveBaseMoteurGaucheEncoder);
	AddChild("Drive",      m_Drive);
	AddChild("Regulateur", m_pidController);

	m_logger.set_min_level(wpi::WPI_LOG_INFO);

	WPI_DEBUG(m_logger, "Moteur droit sur le canal  PWM " << m_DriveBaseMoteurDroit.GetChannel()
	                 << " avec encodeur sur les canaux DIO " << kBaseMobileEncoderD_DioChannelA << " et " << kBaseMobileEncoderD_DioChannelB << ".");
	WPI_DEBUG(m_logger, "Moteur gauche sur le canal PWM " << m_DriveBaseMoteurGauche.GetChannel()
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
	if (m_direction == eDirection::Crochet)
	{
		xSpeed *= -1.0;
	}
	m_Drive.ArcadeDrive(xSpeed, zRotation);

	// Afficher à la console seulement si une des valeurs changent de 5% par rapport à la dernière.
	// Un message imprimé à chaque 20 ms est trop verbeux.
	if ((std::fabs((xSpeed - m_lastXSpeed)/m_lastXSpeed) > 0.05) || (std::fabs((zRotation - m_lastZRotation)/m_lastZRotation) > 0.05))
	{
		WPI_DEBUG2(m_logger, "xSpeed:"    << wpi::format("%5.2f", xSpeed) 
		                  << "zRotation:" << wpi::format("%5.2f", zRotation)
		                  << "Distances [EncD, EncG]: " << wpi::format("%5.2f", m_DriveBaseMoteurDroitEncoder.GetDistance()) << " " << wpi::format("%5.2f", m_DriveBaseMoteurGaucheEncoder.GetDistance())
		                  << "Rates     [EncD, EncG]: " << wpi::format("%5.2f", m_DriveBaseMoteurDroitEncoder.GetRate())     << " " << wpi::format("%5.2f", m_DriveBaseMoteurGaucheEncoder.GetRate()));

		// Enregistrer la vitesse courrant pour la comparer la prochaine fois qu'on exécute
		// cette méthode avec une nouvelle valeur de 'speed'.
		m_lastXSpeed    = xSpeed;
		m_lastZRotation = zRotation;
	}
}

void sysBaseMobile::setDirection(eDirection direction)
{
	m_direction = direction;
}

void sysBaseMobile::setSpeed(double speed)
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__ << " vitesse: " << wpi::format("%6.3f", speed));
	m_speed_sp = speed;
	m_Drive.ArcadeDrive(-m_speed_sp, m_rotation_rate_sp);
}

void sysBaseMobile::EnablePID(double k_p, double k_i, double k_d, double k_f)
{
	m_pidController.SetInputRange(-10.0, 10.0); // m/s TODO TDB
	m_pidController.SetOutputRange(-10.0, 10.0); // m/s
	m_pidController.SetSetpoint((m_DriveBaseMoteurGaucheEncoder.GetRate() + m_DriveBaseMoteurDroitEncoder.GetRate()) / 2.0);
	m_pidController.SetPID(k_p, k_i, k_d, k_f);
	WPI_DEBUG(m_logger, "pid: " << wpi::format("%5.2f", m_pidController.GetP())
	                 << ", "    << wpi::format("%5.2f", m_pidController.GetI())
	                 << ", "    << wpi::format("%5.2f", m_pidController.GetD())
	                 << ", "    << wpi::format("%5.2f", m_pidController.GetF()));
	m_pidController.Reset();
	m_pidController.Enable();
}

void sysBaseMobile::DisablePID()
{
	m_pidController.Disable();
	m_pidController.SetPID(0.0, 0.0, 0.0, 0.0);
	m_pidController.Reset();
}

frc::PIDSourceType sysBaseMobile::getPIDSourceType()
{
	return m_pidController.GetPIDSourceType();
}

double sysBaseMobile::getPositionMin()
{
	return -std::numeric_limits<double>::infinity();
}

double sysBaseMobile::getPositionMax()
{
	return std::numeric_limits<double>::infinity();
}

double sysBaseMobile::getSpeedMax()
{
	return speedMax;
}

double sysBaseMobile::getAccelMax()
{
	return accelMax;
}

double sysBaseMobile::getPositionFB()
{
	return m_pidSrcEncAvg.PIDGet();
}

void sysBaseMobile::setPositionSP(double position)
{
	WPI_ERROR(m_logger, "Regulateur PID en vitesse.");
	throw(std::logic_error("Regulateur PID en vitesse."));
}

double sysBaseMobile::getSpeedFB()
{
	return m_pidSrcEncAvg.PIDGet();
}

void sysBaseMobile::setSpeedSP(double speed)
{
	m_pidController.SetSetpoint(speed);
	// WPI_DEBUG2(m_logger, GetName() << " " << __func__ << " vitesse: " << wpi::format("%6.3f", speed) << wpi::format(", %6.3f", m_pidController.GetSetpoint()));
}

void sysBaseMobile::resetPosition()
{
	m_DriveBaseMoteurDroitEncoder.Reset();
	m_DriveBaseMoteurGaucheEncoder.Reset();
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
