/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BaseMobileTurnPidOutput.h"

#include "subsystems/BaseMobile.h"
#include <wpi/Format.h>

#include "Logger.h"


sysBaseMobileTurnPidOutput::sysBaseMobileTurnPidOutput(sysBaseMobile * base_mobile)
	: m_BaseMobile(base_mobile)
	, m_logger(log_func)
{
	m_logger.set_min_level(wpi::WPI_LOG_INFO);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void sysBaseMobileTurnPidOutput::PIDWrite(double output)
{
	if (m_BaseMobile)
	{
		WPI_DEBUG2(m_logger, __func__ << " output: " << wpi::format("%6.3f", output));
		m_BaseMobile->setRotationRate(output);
	}
}
