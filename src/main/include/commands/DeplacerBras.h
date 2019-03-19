/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <wpi/Logger.h>

class cmdDeplacerBras : public frc::Command
{
 public:
	cmdDeplacerBras(double position);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

 private:
	const double m_Position;

	double m_lastTime;

	/// Logger du sous-système.
	wpi::Logger m_logger;
};
