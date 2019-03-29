/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/PIDOutput.h>

class sysBaseMobile;

class sysBaseMobilePidOutput : public frc::PIDOutput
{
 public:
	sysBaseMobilePidOutput(sysBaseMobile * base_mobile);
	virtual ~sysBaseMobilePidOutput();

	/// name Méthodes qu'on peut overrider.
	/// @{
	virtual void PIDWrite(double output);
	/// @}

 private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	sysBaseMobile *m_BaseMobile;
};
