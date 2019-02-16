/*
 * Logger.cpp
 *
 *  Created on: Dec. 30, 2018
 *      Author: Philippe Brais
 */

#include <iomanip>
#include <iostream>
#include <string>

#include <frc/DriverStation.h>
#include <frc/Timer.h>
#include <wpi/Logger.h>


void log_func(unsigned int level, const char* file, unsigned int line, const char* msg)
{
	if (level >= wpi::WPI_LOG_ERROR)
	{
		frc::DriverStation::ReportError(true, 0, wpi::Twine(msg), wpi::Twine(std::string(file) + ":" + std::to_string(line)), wpi::Twine());
	}
	else if (level >= wpi::WPI_LOG_WARNING)
	{
		frc::DriverStation::ReportError(false, 0, wpi::Twine(msg), wpi::Twine(std::string(file) + ":" + std::to_string(line)), wpi::Twine());
	}
	else if (level >= wpi::WPI_LOG_INFO)
	{
		std::cout << std::setw(9) << std::fixed << std::setprecision(6) << frc::Timer::GetFPGATimestamp() << " "
		          << msg << std::endl;
	}
	else
	{
		std::cout << std::setw(9) << std::fixed << std::setprecision(6) << frc::Timer::GetFPGATimestamp() << " "
		          << file << ":" << line << " "
		          << msg << std::endl;
	}
}
