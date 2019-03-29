/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file BaseMobile.h
/// \brief Sous-système représentant la base mobile avec les quatre moteurs et encodeurs.

#include <frc/commands/Subsystem.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Encoder.h>
#include <frc/PIDController.h>
#include <frc/VictorSP.h>
#include <wpi/Logger.h>

#include "ISubsystem.h"
#include "RobotMap.h"
#include "subsystems/BaseMobilePidOutput.h"
#include "subsystems/BaseMobilePidSource.h"

enum class eDirection
{
	Bras,
	Crochet,
};

class sysBaseMobile : public frc::Subsystem, public ISubsystem
{
 private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	/// @name Les encodeurs sur les gearbox.
	/// @{
	frc::Encoder m_DriveBaseMoteurDroitEncoder;
	frc::Encoder m_DriveBaseMoteurGaucheEncoder;
	/// @}

	/// @name Les contrôleurs de moteurs sont quatre VEX PRO Victor SP (P/N: 217-9090).
	/// @{
	frc::VictorSP m_DriveBaseMoteurDroit;
	frc::VictorSP m_DriveBaseMoteurGauche;
	/// @}

	frc::DifferentialDrive m_Drive;

	eDirection m_direction;

	/// Vitesse linéaire désirée du moteur (m/s)
	double m_speed_sp;

	/// Vitesse angulaire désirée du moteur (rad/s)
	double m_rotation_rate_sp;

	/// \name Régulateur PID pour le contrôle de vitesse.
	/// @{
	sysBaseMobilePidSource m_pidSrcEncAvg;
	frc::PIDController     m_pidController;
	sysBaseMobilePidOutput m_pidOutput;
	/// @}

	/// \name Limites physique du bras.
	/// Valeurs à déterminer pendant des tests.
	/// @{
	static double speedMax;
	static double accelMax;
	/// @}

	/// Logger du sous-système.
	wpi::Logger m_logger;

	/** \name Variables pour comparer avec les nouvelles valeurs, de vitesse, de rotation, etc.
	 *
	 * Ceci permet d'afficher un message à la console que quand il y a changement.
	 */
	/// @{
	double m_lastXSpeed = 0.0;
	double m_lastZRotation = 0.0;
	/// @}


 public:
	sysBaseMobile();
	void InitDefaultCommand() override;

	void ArcadeDrive(double xSpeed, double zRotation);

	void setDirection(eDirection direction);

	void setSpeed(double speed);

	/** Activer le régulateur PID du sous-système
	 *
	 * À l'activation du contrôleur, la vitesse désirée sera celle actuelle du
	 * sous-système.
	 *
	 * \param k_p Constante proportionnelle
	 * \param k_i Constante intégrale
	 * \param k_d Constante dérivée
	 * \param k_d Constante feed-forward
	 */
	void EnablePID(double k_p = 0.0, double k_i = 0.0, double k_d = 0.0, double k_f = 0.0);
	void DisablePID();

	frc::PIDSourceType getPIDSourceType();

	double getPositionMin();

	double getPositionMax();

	double getSpeedMax();

	double getAccelMax();

	double getPositionFB();

	void setPositionSP(double position);

	double getSpeedFB();

	void setSpeedSP(double speed);

	virtual void resetPosition();

	void PutSmartDashboard();
};
