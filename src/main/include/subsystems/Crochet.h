/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Crochet.h
/// \brief Sous-système représentant le crochet pour transporter un panneaux de trappe.
#include <frc/Talon.h>
#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
class sysCrochet : public frc::Subsystem
{
 private:
	frc::Talon m_CrochetMoteur {kCrochetMoteur_PwmChannel};

 public:
	sysCrochet();
	void InitDefaultCommand() override;

	void setSpeed(double speed);
};
