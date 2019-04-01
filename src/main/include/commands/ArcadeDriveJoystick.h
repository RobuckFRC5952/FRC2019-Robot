/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Joystick.h>
#include <wpi/Logger.h>


class sysBaseMobile;

class cmdArcadeDriveJoystick : public frc::Command
{
 public:
	cmdArcadeDriveJoystick(frc::Joystick & joystick, sysBaseMobile & sys_base_mobile);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

 private:
	frc::Joystick & m_joystick;
	sysBaseMobile & m_sysBaseMobile;

	/** \name Variables pour comparer avec leurs nouvelles valeurs.
	 *
	 * Ceci permet d'afficher un message à la console que quand il y a changement.
	 */
	/// @{
	double m_lastTime;
	/// @}

	/// Logger du sous-système.
	wpi::Logger m_logger;
};
