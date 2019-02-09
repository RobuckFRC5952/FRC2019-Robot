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
constexpr int kBaseMobileEncoderD_DioChannelA = 0;
constexpr int kBaseMobileEncoderG_DioChannelB = 1;
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

/// \name Boutons des joystick Logitech ATK3
/// @{
constexpr int kJoystickATK3Trigger = 1; // \todo Vérifier
/// @}

/// \name Boutons du joystick Logitech Extreme 3D Pro
/// @{
constexpr int kJoystick3DProTrigger = 1;
/// @}

#ifdef USE_LOGITECH_ATK3
/// Boutton Trigger pour ...
constexpr int kJoystickTrigger = kJoystickATK3Trigger;
#endif
#ifdef USE_LOGITECH_X3DPRO
/// Boutton Trigger pour ...
constexpr int kJoystickTrigger = kJoystick3DProTrigger;
#endif
