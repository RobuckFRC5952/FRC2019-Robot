/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Bras.h
/// \brief Sous-système représentant le bras qui peut monter/descentre la pince.

#include <memory>

#include <frc/commands/PIDSubsystem.h>
#include <frc/Encoder.h>
#include <frc/PWMVictorSPX.h>

#include "RobotMap.h"

#include <wpi/Logger.h>


class sysBras : public frc::PIDSubsystem
{
 private:
	/// Le moteur du bras.
	frc::PWMVictorSPX m_BrasMoteur {kBrasMoteur_PwmChannel};

	/// L'encodeur sur le moteur.
	frc::Encoder m_encoder { kBrasEncoder_DioChannelA, kBrasEncoder_DioChannelB, true, frc::Encoder::EncodingType::k4X };

	std::shared_ptr<frc::PIDController> m_pidController;

	/// Logger du sous-système.
	wpi::Logger m_logger;

	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);

 public:
	sysBras();

	void InitDefaultCommand() override;

	void EnablePID(double k_p, double k_i, double k_d, double k_f);
	void DisablePID();

	double getPosition();
	void setPosition(double radian);

	void resetEnc();
	// void setSpeed(double speed);

	void PutSmartDashboard();
};
