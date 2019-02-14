/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Bras.h
/// \brief Sous-système représentant le bras qui peut monter/descentre la pince.

#include <frc/commands/Subsystem.h>
#include <frc/PWMVictorSPX.h>

#include "RobotMap.h"

class sysBras : public frc::Subsystem
{
 public:
	sysBras();
	void InitDefaultCommand() override; 

private:
	frc::PWMVictorSPX m_BrasMoteur {kBrasMoteur_PwmChannel};
};