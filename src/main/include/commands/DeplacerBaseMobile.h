/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "cinematique/DeplaceMoteur.h"

class cmdDeplacerBaseMobile : public cmdDeplaceMoteur
{
 public:
	explicit cmdDeplacerBaseMobile(double distance);	// TODO Vitesse initiale et finale
	virtual void Initialize() override;
	virtual void Execute() override;
	virtual bool IsFinished() override;
	virtual void End() override;
	virtual void Interrupted() override;

 private:
	/// La distance à parcourir.
	double m_distance;
};
