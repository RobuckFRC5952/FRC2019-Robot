/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/// \file LancerBallon.h
/// \brief Commande pour faire tourner les moteurs de la pince pour éjecter le ballon.

#pragma once

#include <frc/commands/Command.h>

class cmdLancerBallon : public frc::Command
{
 public:
	cmdLancerBallon();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};
