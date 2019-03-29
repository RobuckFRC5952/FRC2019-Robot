/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/PIDSource.h>

namespace frc
{
	class Encoder;
}

class sysBaseMobilePidSource : public frc::PIDSource
{
 public:
	sysBaseMobilePidSource(frc::Encoder &left, frc::Encoder &right);
	virtual ~sysBaseMobilePidSource();

	/// name Méthodes qu'on peut overrider.
	/// @{
	virtual void SetPIDSourceType(frc::PIDSourceType pidSource);
	virtual frc::PIDSourceType GetPIDSourceType() const;
	virtual double PIDGet();
	/// @}

 private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	frc::Encoder &m_left;
	frc::Encoder &m_right;
	frc::PIDSourceType m_pidSourceType;
};
