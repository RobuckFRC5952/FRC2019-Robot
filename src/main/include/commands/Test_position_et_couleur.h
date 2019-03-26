/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>
#include <frc/commands/PrintCommand.h>

class Test_position_et_couleur : public frc::CommandGroup {	
 public:
 //Tourne le moteur pendant 3 mètre à 1/2 de sa vitesse
AddSequential (new frc::PrintCommand("\nTourne le moteur à 1, avec acceleration de 0,30"));
// AddSequential (new WaitCommand(3.0));

// AddSequential (new PrintCommand("\nTourner de 90 degrés"));
// AddSequential (new WaitCommand(3.0));

  Test_position_et_couleur();
};
