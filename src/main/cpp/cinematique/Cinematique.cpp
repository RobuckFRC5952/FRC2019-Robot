/*
 * Cinematique.cpp
 *
 *  Created on: Jan. 19, 2019
 *      Author: Philippe Brais
 */

#include "cinematique/Cinematique.h"

#include <iomanip>


std::ostringstream print_vt_profile(std::vector<Vt> const & profile)
{
	std::ostringstream ss;
	std::size_t phase = 0;
	for (Vt vt: profile)
	{
		ss << "\nphase " << phase++ << " v(" << std::fixed << std::setw(6) << std::setprecision(3) << vt.m_time  << ") = "
		                                     << std::fixed << std::setw(5) << std::setprecision(2) << vt.m_speed << " L/s";
	}
	return ss;
}
