/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/** \file RobotMap.h
 * \brief Ensemble des ports utilisés du RoboRIO.
 *
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 * 
 * \sa [NI roboRIO User Manual](http://www.ni.com/pdf/manuals/374474a.pdf)
 */

/// \name Ports d'entrée / sortie numérique (DIO)
/// @{
constexpr int DriveBaseMoteurDroitEncoderChannelA = 0;
constexpr int DriveBaseMoteurDroitEncoderChannelB = 1;
constexpr int DriveBaseMoteurGaucheEncoderChannelA = 2;
constexpr int DriveBaseMoteurGaucheEncoderChannelB = 3;
/// @}

/// \name Ports de modulation de largeur d'impulsion (PWM)
/// @{
constexpr int kBaseMobileMoteursD_PwmChannel = 0;
constexpr int kBaseMobileMoteursG_PwmChannel = 1;
// même pwm pour les 2 moteur de la pince
constexpr int kPinceMoteurD_PwmChannel = 3;
constexpr int kPinceMoteurG_PwmChannel = 3;
constexpr int kBrasMoteur_PwmChannel = 4;
constexpr int kCrochetMoteur_PwmChannel = 5;
constexpr int kRampeMoteur_PwmChannel = 2;
/// @}

/// Port du joystick utilisé
constexpr int kJoystickPort = 0;

// #define USE_LOGITECH_ATK3
#define USE_LOGITECH_X3DPRO

/// \name Boutons du joystick Logitech Extreme 3D Pro
/// @{
constexpr int kJoystick3DProTrigger = 1;
constexpr int kJoystick3DProAttrapper_ballon = 2; // TBC
constexpr int kJoystick3DProPousser_ballon = 3; // TBC
constexpr int kJoystick3DProAttrapper_la_hatch = 4; // TBC
constexpr int kJoystick3DProPousser_la_hatch = 5; // TBC
constexpr int kJoystick3DProThrottle = 0;
/// @}

/// \name Boutons des joystick Logitech ATK3
/// @{
constexpr int kJoystickATK3Trigger = 1;
constexpr int kJoystickATK3Attrapper_ballon = 2;
constexpr int kJoystickATK3Pousser_ballon = 3;
constexpr int kJoystickATK3Attrapper_la_hatch = 4;
constexpr int kJoystickATK3Pousser_la_hatch = 5;
constexpr int kJoystickATK3Throttle = 0;
/// @}

#ifdef USE_LOGITECH_ATK3
/// Boutton Trigger pour ...
constexpr int kJoystickTrigger = kJoystickATK3Trigger;
constexpr int kJoystickattrapper_ballon = kJoystickATK3Attrapper_ballon;
constexpr int kJoystickpousser_ballon = kJoystickATK3Pousser_ballon;
constexpr int kJoystickattrapper_la_hatch = kJoystickATK3Attrapper_la_hatch;
constexpr int kJoystickpousser_la_hatch = kJoystickATK3Pousser_la_hatch;
constexpr int kJoystickthrottle = kJoystickATKTthrottle;
#endif
#ifdef USE_LOGITECH_X3DPRO
/// Boutton Trigger pour ...
constexpr int kJoystickTrigger = kJoystick3DProTrigger;
constexpr int kJoystickattrapper_ballon = kJoystick3DProAttrapper_ballon;
constexpr int kJoystickpousser_ballon = kJoystick3DProPousser_ballon;
constexpr int kJoystickattrapper_la_hatch = kJoystick3DProAttrapper_la_hatch;
constexpr int kJoystickpousser_la_hatch = kJoystick3DProPousser_la_hatch;
constexpr int kJoystickthrottle = kJoystick3DProThrottle;
#endif
