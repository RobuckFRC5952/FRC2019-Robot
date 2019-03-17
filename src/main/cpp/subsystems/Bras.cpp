/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#define _USE_MATH_DEFINES 

#include "subsystems/Bras.h"

#include <cmath>

#include <frc/PIDSource.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <wpi/Format.h>

#include "Logger.h"


sysBras::sysBras()
	 : PIDSubsystem(__func__, 1.0, 0.0, 1.0, 0.0)
	 , m_logger(log_func)
{
	m_BrasMoteur.SetInverted(true);

#define MONTECHARGE
#ifdef MONTECHARGE
	double m_gearbox_ratio = 71.0;
	double m_encoder_ratio =  7.0;
	double RadPerPulse = 2.0 * M_PI / (m_gearbox_ratio * m_encoder_ratio);
	m_encoder.SetDistancePerPulse(RadPerPulse);
#else
	// Encodeur: 2048 pulses par révolution.
	const int pulses_tour = 2048;

	// Convertir en radian la distance de l'encodeur.
	m_encoder.SetDistancePerPulse( (2.0 * M_PI) / pulses_tour);
#endif

	// Spécifier pour le régulateur que l'encodeur sera utilisé en déplacement et non pas vitesse.
	m_encoder.SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	m_encoder.SetName("Enc");

	// Récupérer le PID du sous-système pour être capable de configurer ces constantes.
	m_pidController = GetPIDController();

	m_logger.set_min_level(wpi::WPI_LOG_INFO);

	frc::SmartDashboard::PutNumber("SetPoint", 0.0);
	frc::SmartDashboard::PutNumber("FeedBack", 0.0);
	frc::SmartDashboard::PutNumber("Error",    0.0);
	frc::SmartDashboard::PutNumber("Commande", 0.0);

	frc::SmartDashboard::PutNumber("PutGET", 0.0);
}

void sysBras::InitDefaultCommand()
{
	WPI_DEBUG3(m_logger, GetName() + " " + __func__);
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

double sysBras::ReturnPIDInput()
{
	WPI_DEBUG2(m_logger, GetName() << " " << __func__ << " m_encoder.GetDistance " << m_encoder.GetDistance());
	return m_encoder.GetDistance();
}

void sysBras::UsePIDOutput(double output)
{
	double plus = frc::SmartDashboard::GetNumber("PutGET", 0.0);
	WPI_DEBUG2(m_logger, GetName() << " " << __func__ << " output: " << output << ", plus: " << plus);
	m_BrasMoteur.Set(output + plus);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void sysBras::EnablePID(double k_p, double k_i, double k_d, double k_f)
{
	// Activer le régulateur PID.
	WPI_DEBUG(m_logger, "Activer le regulateur, constantes: "
	               <<   "P " << wpi::format("%5.2f", k_p)
	               << ", I " << wpi::format("%5.2f", k_i)
	               << ", D " << wpi::format("%5.2f", k_d)
	               << ", F " << wpi::format("%5.2f", k_f));

	m_pidController->SetPID(k_p, k_i, k_d, k_f);
	m_pidController->SetSetpoint(m_encoder.GetDistance());
	m_pidController->SetInputRange( 0.0, 1.2); // rad
	m_pidController->SetOutputRange(-1.0, 1.0); // rad
	m_pidController->Reset();
	Enable();
}

void sysBras::DisablePID()
{
	WPI_DEBUG3(m_logger, GetName() + " " + __func__);

	// Désactiver le régulateur PID.
	// Disable();
	m_pidController->Reset();
}

double sysBras::getPosition()
{
	return m_encoder.GetDistance();
}

void sysBras::setPosition(double radian)
{
	m_pidController->SetSetpoint(radian);
	WPI_DEBUG2(m_logger, GetName() << " " << __func__ << " radian: " << wpi::format("%6.3f", radian) << wpi::format(", %6.3f", m_pidController->GetSetpoint()));
}

// void sysBras::setSpeed(double speed)
// {
// 	WPI_DEBUG3(m_logger,"sysBras::setSpeed vitesse: " << speed);
// 	m_BrasMoteur.Set(speed);
// }

void sysBras::resetEnc()
{
	m_encoder.Reset();
}

void sysBras::PutSmartDashboard()
{
	// Afficher les données de l'encodeur.
	std::string const & name = m_encoder.GetName();
	frc::SmartDashboard::PutNumber( name + "_Count",     m_encoder.Get());
	frc::SmartDashboard::PutNumber( name + "_Raw",       m_encoder.GetRaw());
	frc::SmartDashboard::PutNumber( name + "_Distance",  m_encoder.GetDistance());
	frc::SmartDashboard::PutNumber( name + "_Rate",      m_encoder.GetRate());
	frc::SmartDashboard::PutBoolean(name + "_Direction", m_encoder.GetDirection());
	frc::SmartDashboard::PutBoolean(name + "_Stopped",   m_encoder.GetStopped());

	// Afficher ces données dans des LinePlots du SmartDashboard.
	frc::SmartDashboard::PutNumber("SetPoint", m_pidController->GetSetpoint());
	frc::SmartDashboard::PutNumber("FeedBack", m_encoder.PIDGet());
	frc::SmartDashboard::PutNumber("Error",    m_pidController->GetError());
	frc::SmartDashboard::PutNumber("Commande", m_pidController->Get());
}
