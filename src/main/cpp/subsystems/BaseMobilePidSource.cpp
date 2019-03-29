/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BaseMobilePidSource.h"

#include <frc/Encoder.h>

sysBaseMobilePidSource::sysBaseMobilePidSource(frc::Encoder & left, frc::Encoder & right)
: m_left(left)
, m_right(right)
{
}

sysBaseMobilePidSource::~sysBaseMobilePidSource()
{
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void sysBaseMobilePidSource::SetPIDSourceType(frc::PIDSourceType pidSource)
{
	m_pidSourceType = pidSource;
	m_left.SetPIDSourceType(pidSource);
	m_right.SetPIDSourceType(pidSource);
}

frc::PIDSourceType sysBaseMobilePidSource::GetPIDSourceType() const
{
	return m_left.GetPIDSourceType();
}

double sysBaseMobilePidSource::PIDGet()
{
	double average = 0.0;
	if (m_pidSourceType == frc::PIDSourceType::kDisplacement)
	{
		average = (m_left.GetDistance() + m_right.GetDistance()) / 2.0;
	}
	if (m_pidSourceType == frc::PIDSourceType::kRate)
	{
		average = (m_left.GetRate() + m_right.GetRate()) / 2.0;
	}
	return average;
}
