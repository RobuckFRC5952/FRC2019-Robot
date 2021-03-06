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

#include "commands/ArcadeDriveImmobile.h"
#include "commands/ArcadeDriveJoystick.h"
#include "ISubsystem.h"
#include "RobotMap.h"
#include "subsystems/BaseMobilePidOutput.h"
#include "subsystems/BaseMobilePidSource.h"
#include "subsystems/BaseMobileTurnPidOutput.h"


class AHRS;

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

	AHRS * m_ahrs; // navX MXP

	/// Default Commands
	cmdArcadeDriveImmobile m_cmdArcadeDriveImmobile;
	cmdArcadeDriveJoystick m_cmdArcadeDriveJoystick;

	eDirection m_direction;

	/// Vitesse linéaire désirée du moteur (m/s)
	double m_speed_sp;

	/// Vitesse angulaire désirée du moteur (rad/s)
	double m_rotation_rate_sp;

	/// \name Régulateur PID pour le contrôle de vitesse.
	/// @{
	sysBaseMobilePidSource m_pidSrcEncAvg;
	sysBaseMobilePidOutput m_pidOutput;
	frc::PIDController     m_pidController;
	static double m_speed_kP;
	static double m_speed_kI;
	static double m_speed_kD;
	static double m_speed_kF;
	/// @}

	/// \name Régulateur PID pour le contrôle de rotation.
	/// @{
	sysBaseMobileTurnPidOutput m_turnPidOutput;
	frc::PIDController * m_turnPidController;
	static double m_turn_kP;
	static double m_turn_kI;
	static double m_turn_kD;
	static double m_turn_kF;
	static double const kToleranceDegrees;
	/// @}

	/// \name Limites physique de la base mobile.
	/// Valeurs à déterminer pendant des tests.
	/// @{
	static double m_speedMax;
	static double m_accelMax;
	static double m_rotationMax;
	static double m_rot_accelMax;
	/// @}

	static char const * m_key_direction;

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
	void SetImmobileCommand();

	void ArcadeDrive(double xSpeed, double zRotation);

	eDirection getDirection();
	void setDirection(eDirection direction);

	void setSpeed(double speed);
	void setRotationRate(double rotation_rate);

	bool IsEnabled();

	void EnablePID();

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
	void EnableSpeedPID(double k_p, double k_i = 0.0, double k_d = 0.0, double k_f = 0.0);
	void EnableTurnPID(double k_p, double k_i = 0.0, double k_d = 0.0, double k_f = 0.0);

	void DisablePID();

	frc::PIDSourceType getPIDSourceType();

	double getPositionMin();

	double getPositionMax();

	double getSpeedMax();

	double getAccelMax();

	double getRotationSpeedMax();

	double getRotationAccelMax();

	double getPositionFB();

	void setPositionSP(double position);

	double getSpeedFB();

	void setSpeedSP(double speed);

	double getRotationFB();

	void setRotationSP(double rotation);

	virtual void resetPosition();

	void PutSmartDashboard();
};
