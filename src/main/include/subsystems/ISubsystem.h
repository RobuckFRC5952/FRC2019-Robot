/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/// \file ISubsystem.h
/// \brief Interface commune des sous-systèmes.

#include <frc/PIDSource.h>


class ISubsystem
{
 public:

	/** Demander le type de régulateur.
	 * \return \c kDisplacement ou \c kRate
	 */
	virtual frc::PIDSourceType getPIDSourceType() = 0;

	/// \name Limites physique du sous-système.
	/// @{
	virtual double getPositionMin() = 0;
	virtual double getPositionMax() = 0;
	virtual double getSpeedMax() = 0;
	virtual double getAccelMax() = 0;
	/// @}

	/// \name Accès au régulateur PID du sous-système.
	/// @{
	virtual double getPositionFB() = 0;
	virtual void   setPositionSP(double position) = 0;
	/// @}

	/// Remettre à zéro la position du sous-système.
	virtual void   resetPosition() = 0;
};
