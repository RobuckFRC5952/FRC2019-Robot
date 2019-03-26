/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Test_position_et_couleur.h"

#include <frc/commands/PrintCommand.h>
#include <frc/commands/WaitCommand.h>


Test_position_et_couleur::Test_position_et_couleur() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.

	//Tourne le moteur pendant 3 mètre à 1/2 de sa vitesse
	AddSequential (new frc::PrintCommand("\nTourne le moteur à 1, avec acceleration de 0,30"));
	AddSequential (new frc::WaitCommand(3.0));

	AddSequential (new frc::PrintCommand("\nTourner de 90 degrés"));
	AddSequential (new frc::WaitCommand(3.0));
}
