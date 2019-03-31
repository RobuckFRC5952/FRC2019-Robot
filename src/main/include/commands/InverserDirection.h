/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/InstantCommand.h>
#include <wpi/Logger.h>

#include "../subsystems/BaseMobile.h"


class InverserDirection : public frc::InstantCommand
{
 public:
	InverserDirection();
	void Initialize() override;

 private:
	/// Logger de la commande.
	wpi::Logger m_logger;
};
