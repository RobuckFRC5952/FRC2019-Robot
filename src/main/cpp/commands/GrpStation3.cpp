/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/GrpStation3.h"

#include <frc/commands/PrintCommand.h>
#include <frc/commands/WaitCommand.h>

#include "commands/DeplacerBaseMobile.h"
#include "commands/TournerBaseMobile.h"


cmdGrpStation3::cmdGrpStation3()
	 : CommandGroup(__func__)
{
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
	double distance = 0.0;
	double rotation = 0.0;

	AddSequential(new frc::PrintCommand(GetName() + " Avancer de 3.0 m."));
	distance = 3.0;
	AddSequential(new cmdDeplacerBaseMobile(distance));

	AddSequential(new frc::PrintCommand(GetName() + " Tourner de 45 degres."));
	rotation = 45.0;
	AddSequential(new cmdTournerBaseMobile(rotation));

	AddSequential(new frc::PrintCommand(GetName() + " Avancer de sqrt(2) m."));
	distance = std::sqrt(2.0);
	AddSequential(new cmdDeplacerBaseMobile(distance));

	AddSequential(new frc::PrintCommand(GetName() + " Tourner de -45 degres."));
	rotation = -45.0;
	AddSequential(new cmdTournerBaseMobile(rotation));

	AddSequential(new frc::PrintCommand(GetName() + " Avancer de 2.5 m."));
	distance = 2.5;
	AddSequential(new cmdDeplacerBaseMobile(distance));

	AddSequential(new frc::PrintCommand(GetName() + " Tourner de -90 degres."));
	rotation = -90.0;
	AddSequential(new cmdTournerBaseMobile(rotation));

	// AddSequential(new frc::PrintCommand(GetName() + " Avancer de 2.5 m."));
	// distance = 1.0;
	// AddSequential(new cmdDeplacerBaseMobile(distance));
}
