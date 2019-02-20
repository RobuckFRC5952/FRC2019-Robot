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
constexpr int kBaseMobileEncoderD_DioChannelB = 1;
constexpr int kBaseMobileEncoderG_DioChannelA = 2;
constexpr int kBaseMobileEncoderG_DioChannelB = 3;
constexpr int kCrochetLimitSwitchBas_DioChannel  = 7;
constexpr int kCrochetLimitSwitchHaut_DioChannel = 6;
/// @}

/// \name Ports de modulation de largeur d'impulsion (PWM)
/// @{
constexpr int kBaseMobileMoteursD_PwmChannel = 0;
constexpr int kBaseMobileMoteursG_PwmChannel = 1;
constexpr int kBrasMoteur_PwmChannel = 4;
constexpr int kPinceMoteurs_PwmChannel = 3;
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
constexpr int kJoystick3DProInvDir = 2;
constexpr int kJoystick3DProMonter_bras = 10;
constexpr int kJoystick3DProBaisser_bras = 9;
constexpr int kJoystick3DProAttrapper_ballon = 5;
constexpr int kJoystick3DProPousser_ballon = 3;
constexpr int kJoystick3DProAttrapper_la_hatch = 4;
constexpr int kJoystick3DProPousser_la_hatch = 6;
constexpr int kJoystick3DProDeployer_la_rampe = 11;
constexpr int kJoystick3DProRemonter_la_rampe = 12;
constexpr int kJoystick3DProThrottle = 0;
/// @}
/// \name Boutons des joystick Logitech ATK3
/// @{
constexpr int kJoystickATK3Trigger = 1;
constexpr int kJoystickATK3InvDir = 2;
constexpr int kJoystickATK3Monter_bras = 11;
constexpr int kJoystickATK3Baisser_bras = 10;
constexpr int kJoystickATK3Attrapper_ballon = 2;
constexpr int kJoystickATK3Pousser_ballon = 3;
constexpr int kJoystickATK3Attrapper_la_hatch = 4;
constexpr int kJoystickATK3Pousser_la_hatch = 5;
constexpr int kJoystickATK3Deployer_la_rampe = 8;
constexpr int kJoystickATK3Remonter_la_rampe = 9;
constexpr int kJoystickATK3Throttle = 0;
/// @}

#ifdef USE_LOGITECH_ATK3
/// Boutton Trigger pour ...
constexpr int kJoystickTrigger = kJoystickATK3Trigger;
constexpr int kJoystickInvDir = kJoystickATK3InvDir;
constexpr int kJoystickattrapper_ballon = kJoystickATK3Attrapper_ballon;
constexpr int kJoystickpousser_ballon = kJoystickATK3Pousser_ballon;
constexpr int kJoystickattrapper_la_hatch = kJoystickATK3Attrapper_la_hatch;
constexpr int kJoystickpousser_la_hatch = kJoystickATK3Pousser_la_hatch;
constexpr int kJoystickthrottle = kJoystickATKTthrottle;
constexpr int kJoystickDeployer_la_rampe = kJoystickATK3Deployer_la_rampe;
constexpr int kJoystickRemonter_la_rampe = kJoystickATK3Remonter_la_rampe;
constexpr int kJoystickMonter_bras = kJoystickATK3Monter_bras;
constexpr int kJoystickBaisser_bras = kJoystickATK3Baisser_bras;
#endif
#ifdef USE_LOGITECH_X3DPRO
/// Boutton Trigger pour ...
constexpr int kJoystickTrigger = kJoystick3DProTrigger;
constexpr int kJoystickInvDir = kJoystick3DProInvDir;
constexpr int kJoystickattrapper_ballon = kJoystick3DProAttrapper_ballon;
constexpr int kJoystickpousser_ballon = kJoystick3DProPousser_ballon;
constexpr int kJoystickattrapper_la_hatch = kJoystick3DProAttrapper_la_hatch;
constexpr int kJoystickpousser_la_hatch = kJoystick3DProPousser_la_hatch;
constexpr int kJoystickthrottle = kJoystick3DProThrottle;
constexpr int kJoystickDeployer_la_rampe = kJoystick3DProDeployer_la_rampe;
constexpr int kJoystickRemonter_la_rampe = kJoystick3DProRemonter_la_rampe;
constexpr int kJoystickMonter_bras = kJoystick3DProMonter_bras;
constexpr int kJoystickBaisser_bras = kJoystick3DProBaisser_bras;
#endif
