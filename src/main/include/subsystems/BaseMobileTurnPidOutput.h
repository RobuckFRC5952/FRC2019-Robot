/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/PIDOutput.h>
#include <wpi/Logger.h>


class sysBaseMobile;

class sysBaseMobileTurnPidOutput : public frc::PIDOutput
{
 public:
	sysBaseMobileTurnPidOutput(sysBaseMobile *base_mobile);
	// virtual ~sysBaseMobileTurnPidOutput();

	/// name Méthodes qu'on peut overrider.
	/// @{
	virtual void PIDWrite(double output);
	/// @}

 private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	sysBaseMobile *m_BaseMobile;

	/// Logger du sous-système.
	wpi::Logger m_logger;
};
