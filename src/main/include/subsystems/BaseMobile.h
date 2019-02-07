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

class sysBaseMobile : public frc::Subsystem
{
 private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

 public:
	sysBaseMobile();
	void InitDefaultCommand() override;
};
