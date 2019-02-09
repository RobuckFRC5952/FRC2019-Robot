/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Pince.h
/// \brief Sous-système représentant la pince avec ses deux moteurs pour capturer et éjecter le ballon.
#include <PWMTalonSRX.h>
#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
class sysPince : public frc::Subsystem
{
 private:
 // Moteur TalomSRX pour la pince (elle controle deux moteur)
	frc::PWMTalonSRX m_PinceMoteur {kPinceMoteurG_PwmChannel};

 public:
	sysPince();
	void InitDefaultCommand() override;
};
