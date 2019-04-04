/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "commands/TournerBaseMobile.h"

class testTourneBaseMobile : public cmdTournerBaseMobile
{
 public:
	testTourneBaseMobile();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

 private:
	/// La valeur de \c Rotation dans le \e SmartDashboard.
	double m_rotation;

	/// La valeur de \c Rotation Max dans le \e SmartDashboard.
	double m_rotation_speed_max;

	/// La valeur de \c Rot_Accel dans le \e SmartDashboard.
	double m_rotation_acceleration;

	/// \name Les clés pour chercher les valeurs dans le \e SmartDashboard.
	/// @{
	static char const * m_key_rotation;
	static char const * m_key_rotation_speed_max;
	static char const * m_key_rotation_acceleration;

	static char const * m_key_kP;
	static char const * m_key_kI;
	static char const * m_key_kD;
	static char const * m_key_kF;
	/// @}
};
