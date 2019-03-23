/*
 * Mrua.cpp
 *
 *  Created on: Dec. 16, 2018
 *      Author: Philippe Brais
 */

#include "cinematique/Mrua.h"

#include <cmath>

#include <wpi/Format.h>

Mrua::Mrua(double acceleration, double initial_speed, double initial_position)
: m_acceleration(acceleration)
, m_initial_speed(initial_speed)
, m_initial_position(initial_position)
{
}

void Mrua::Initialize()
{
	m_time.Start();
}

double Mrua::getAcceleration() const
{
	return m_acceleration;
}

double Mrua::getIntegratedSpeed() const
{
	double time = m_time.Get();
	// Note: Si m_acceleration == inf et time == 0.0, le résultat est nan.
	return m_acceleration * (time) + m_initial_speed;
}

double Mrua::getIntegratedSpeed(double time) const
{
	// Note: Si m_acceleration == inf et time == 0.0, le résultat est nan.
	return m_acceleration * (time) + m_initial_speed;
}

double Mrua::getIntegratedPosition() const
{
	double time = m_time.Get();
	// Note: Si m_acceleration == inf et time == 0.0, le résultat est nan.
	return 1.0 / 2.0 * m_acceleration * pow(time, 2) + m_initial_speed * (time) + m_initial_position;
}

double Mrua::getIntegratedPosition(double time) const
{
	// Note: Si m_acceleration == inf et time == 0.0, le résultat est nan.
	return 1.0 / 2.0 * m_acceleration * pow(time, 2) + m_initial_speed * (time) + m_initial_position;
}


std::ostream & operator<<(std::ostream & os, Mrua const & o)
{
	return os << "a: " << o.m_acceleration << ", v0: " << o.m_initial_speed << ", x0: " << o.m_initial_position;
}

wpi::raw_ostream & operator<<(wpi::raw_ostream & os, Mrua const & o)
{
	return os << wpi::format("a: %5.2f", o.m_acceleration) << wpi::format(", v0: %5.2f", o.m_initial_speed) << wpi::format(", x0: %5.2f", o.m_initial_position);
}
