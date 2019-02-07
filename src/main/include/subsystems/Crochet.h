/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file Crochet.h
/// \brief Sous-système représentant le crochet pour transporter un panneaux de trappe.

#include <frc/commands/Subsystem.h>

class sysCrochet : public frc::Subsystem
{
 private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

 public:
	sysCrochet();
	void InitDefaultCommand() override;
};
