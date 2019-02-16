/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Rampe.h
/// \brief Sous-système représentant la rampe et son moteur pour la déployer.

#include <frc/commands/Subsystem.h>
#include <frc/PWMVictorSPX.h>

#include "RobotMap.h"

class sysRampe : public frc::Subsystem
{
 private:
	// Controleur SPX qui s'occupe de la rampe
	frc::PWMVictorSPX m_RampeMoteur{kRampeMoteur_PwmChannel};

 public:
	sysRampe();
	void InitDefaultCommand() override;
	void SetSpeed(double speed);
};
