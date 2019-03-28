/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "cinematique/DeplaceMoteur.h"

#include <wpi/Logger.h>

class cmdDeplacerBras : public cmdDeplaceMoteur
{
 public:
	cmdDeplacerBras(double position);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

 private:
	/** Position du sous-système Bras à atteindre
	 * 
	 * I.e. sysBras::posMin ou sysBras::posMax.
	 */
	double m_position_sp;

	/// La distance à parcourir.
	// double m_distance;

	/** Vitesse maximale du moteur.
	 * 
	 * TODO Peut être offert par le sous-système.
	 */
	double m_speed_max;

	/** La valeur de l'accélération.
	 * 
	 * TODO Peut être offert par le sous-système.
	 */
	double m_acceleration;
};
