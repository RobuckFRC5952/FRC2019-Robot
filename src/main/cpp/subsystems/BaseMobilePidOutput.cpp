/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BaseMobilePidOutput.h"

#include "subsystems/BaseMobile.h"

sysBaseMobilePidOutput::sysBaseMobilePidOutput(sysBaseMobile *base_mobile)
	 : m_BaseMobile(base_mobile)
{
}

sysBaseMobilePidOutput::~sysBaseMobilePidOutput()
{
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void sysBaseMobilePidOutput::PIDWrite(double output)
{
	if (m_BaseMobile)
	{
		m_BaseMobile->setSpeed(output);
	}
}
