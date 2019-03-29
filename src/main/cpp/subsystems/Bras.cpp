/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#define _USE_MATH_DEFINES 

#include "subsystems/Bras.h"

#include <cmath>
#include <stdexcept>

#include <frc/PIDSource.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <wpi/Format.h>

#include "Logger.h"

// Limites physique du sous-système.
double sysBras::posMin   = -1.2; // radian
double sysBras::posMax   =  0.0; // radian
double sysBras::speedMax =  2.0 * M_PI; // radian/sec 	TODO TBD
double sysBras::accelMax =  3.0 * M_PI; // radian/sec²	TODO TBD

sysBras::sysBras()
	 : PIDSubsystem(__func__, 1.0, 0.0, 1.0, 0.0)
	 , m_logger(log_func)
{
	m_BrasMoteur.SetInverted(true);

	// Encodeur: 2048 pulses par révolution.
	const int pulses_tour = 2048;

	// Convertir en radian la distance de l'encodeur.
	m_encoder.SetDistancePerPulse( (2.0 * M_PI) / pulses_tour);

	// Spécifier pour le régulateur que l'encodeur sera utilisé en déplacement et non pas vitesse.
	m_encoder.SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	m_encoder.SetName("Enc");

	// Récupérer le PID du sous-système pour être capable de configurer ces constantes.
	m_pidController = GetPIDController();

	m_logger.set_min_level(wpi::WPI_LOG_INFO);
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
	m_pidController->SetInputRange(posMin, posMax); // rad
	m_pidController->SetOutputRange(-0.5, 0.5); // commande moteur normalisé.
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

frc::PIDSourceType sysBras::getPIDSourceType()
{
	return m_pidController->GetPIDSourceType();
}

double sysBras::getPositionMin()
{
	return posMin;
}

double sysBras::getPositionMax()
{
	return posMax;
}

double sysBras::getSpeedMax()
{
	return speedMax;
}

double sysBras::getAccelMax()
{
	return accelMax;
}

double sysBras::getPositionFB()
{
	return m_encoder.GetDistance();
}

double sysBras::getPositionSP()
{
	return m_pidController->GetSetpoint();
}

void sysBras::setPositionSP(double radian)
{
	m_pidController->SetSetpoint(radian);
	WPI_DEBUG2(m_logger, GetName() << " " << __func__ << " radian: " << wpi::format("%6.3f", radian) << wpi::format(", %6.3f", m_pidController->GetSetpoint()));
}

double sysBras::getSpeedFB()
{
	return m_encoder.GetRate();
}

void sysBras::setSpeedSP(double speed)
{
	WPI_ERROR(m_logger, "Regulateur PID en position.");
	throw(std::logic_error("Regulateur PID en position."));
}

void sysBras::resetPosition()
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
}
