/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include <wpi/Logger.h>


class MonteBras : public frc::Command
{
 public:
	MonteBras();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	void setSpeed();

 private:
	double m_timeout;
	double m_speed;

	/// Logger du sous-système.
	wpi::Logger m_logger;
};
