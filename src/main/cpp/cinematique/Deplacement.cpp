/*
 * Deplacement.cpp
 *
 *  Created on: Jan. 15, 2019
 *      Author: Philippe Brais
 */

#include "cinematique/Deplacement.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "cinematique/Quadratique.h"


Deplacement::Deplacement()
: m_acceleration(std::numeric_limits<double>::infinity())
, m_speed_max(0.0)
{
}

Deplacement::~Deplacement()
{
}


void Deplacement::setAcceleration(double acceleration)
{
	if (acceleration == 0.0)
	{
		throw std::range_error("La methode `getSpeedProfile' divise un nombre par `acceleration', le parametre doit etre plus grand que 0.0 L/s^2.");
	}
	m_acceleration = std::abs(acceleration);
}


void Deplacement::setSpeedMax(double max_speed)
{
	m_speed_max = std::abs(max_speed);
}


std::vector<Vt> Deplacement::getSpeedProfile(double distance, double initial_speed, double final_speed) const
{
	// Vérifier si les vitesses initiale et finale sont entre −m_speed_max et +m_speed_max.
	if (!(((-m_speed_max <= initial_speed) && (initial_speed <= m_speed_max)) &&
	      ((-m_speed_max <= final_speed)   && (final_speed   <= m_speed_max))))
	{
		throw std::range_error("Les vitesses initiale et finale doivent etre limitees entre les vitesses maximales.");
	}

	// Vérifier si les vitesses initiale et finale ont la même direction.
	if ((initial_speed != 0.0) && (final_speed != 0.0) &&
	    (std::signbit(initial_speed) != std::signbit(final_speed)))
	{
		throw std::range_error("Les vitesses initiale et finale doivent conserver la meme direction.");
	}

	// Vérifier si la direction de la vitesse.
	if ((initial_speed != 0.0) &&
	    (std::signbit(initial_speed) != std::signbit(distance)))
	{
		throw std::range_error("Les vitesses initiale et finale doivent avoir le meme signe que la distance à parcourir.");
	}

	// Vérifier si la différence entre les vitesses finale et initiale est
	// atteignable en fonction de la distance voulue et de l'accélélration
	// en cours.
	double delta_time  = std::sqrt(2.0 * std::abs(distance) / m_acceleration);
	double delta_speed = m_acceleration * delta_time;
	if (std::abs(final_speed - initial_speed) > delta_speed)
	{
		throw std::range_error("La vitesse finale n'est pas atteignable.  Augmentez l'acceleration ou diminuez l'ecare entre la vitesse initiale et finale.");
	}

	// Calculer les distances des phases d'accélération (1) et de décélération (3),
	// i.e., de vitesse initiale, à vitesse maximale, à vitesse finale.
	// x = x_0 + v_0·t + ½a·t²
	// v = v_0 + a·t
	double time_1 = (m_speed_max - std::abs(initial_speed)) /  m_acceleration;
	double dist_1 = std::abs(initial_speed) * time_1 + 1.0/2.0 *  m_acceleration * std::pow(time_1, 2.0);
//	std::cout << "Accel: " << std::fixed << std::setw(6) << std::setprecision(1) << dist_1 << "m during " << std::fixed << std::setw(6) << std::setprecision(2) << time_1 << " sec." << std::endl;

	double time_3 = (std::abs(final_speed) - m_speed_max)   / -m_acceleration;
	double dist_3 = std::abs(m_speed_max)    * time_3 + 1.0/2.0 * -m_acceleration * std::pow(time_3, 2.0);
//	std::cout << "Decel: " << std::fixed << std::setw(6) << std::setprecision(1) << dist_3 << "m during " << std::fixed << std::setw(6) << std::setprecision(2) << time_3 << " sec." << std::endl;

	// Si la distance parcourue pendant les phases d'accélération et de décélération n'est pas suffisante,
	if ((dist_1 + dist_3) < std::abs(distance))
	{
		// Ajouter du temps à la vitesse maximale pour combler le manque.
		double dist_2 = std::abs(distance) - (dist_1 + dist_3);
		double time_2 = dist_2 / m_speed_max; // inf possible!
//		std::cout << "Maint: " << std::fixed << std::setw(6) << std::setprecision(1) << dist_2 << "m during " << std::fixed << std::setw(6) << std::setprecision(2) << time_2 << " sec." << std::endl;

		std::vector<Vt> profile;
		double t = 0.0;
		profile.push_back(Vt(t, initial_speed));
		t += time_1;
		profile.push_back(Vt(t, std::copysign(m_speed_max, distance)));
		t += time_2;
		profile.push_back(Vt(t, std::copysign(m_speed_max, distance)));
		t += time_3;
		profile.push_back(Vt(t, final_speed));
		return profile;
	}
	else if ((dist_1 + dist_3) > std::abs(distance))
	{
		// Enlever du temps, i.e., delta_time et diminuer la vitesse de pointe de
		// m_speed_max à speed pour respecter la distance.
		double distance_en_trop = (dist_1 + dist_3) - std::abs(distance);
//		std::cout << "Extra: " << std::fixed << std::setw(6) << std::setprecision(1) << distance_en_trop << "m" << std::endl;

		/* On a un système de deux équations à deux inconnus: speed et delta_time.
		 * Par géométrie la distance à enlever égale:
		 * distance = (speed + m_speed_max)·delta_time                   (eq.1)
		 *
		 * Et l'équation d'accélération égale:
		 * delta_time = (speed − m_speed_max)/(−m_acceleration)          (eq.2)
		 *
		 * En remplacant 'delta_time' de l'équation no. 1 par l'équation no. 2,
		 * on obtient:
		 * (speed + m_speed_max)·(speed − m_speed_max) = −m_acceleration·distance
		 *
		 * Et finalement sous forme d'une équation quadratique:
		 * 1.0·speed² + 0.0·speed + (m_acceleration·distance − m_speed_max²) = 0.0
		 */
		Quadratique speed_eq(1.0, 0.0, m_acceleration*distance_en_trop - m_speed_max*m_speed_max);
		std::vector<double> speeds = speed_eq.getRoots();

//		std::cout << "Roots: "<< speeds[0] << " " << speeds[1] << std::endl;
		double const & max_speed = speeds[0];

		double time_1 = (max_speed - std::abs(initial_speed)) /  m_acceleration;
//		double dist_1 = std::abs(initial_speed) * time_1 + 1.0/2.0 /  m_acceleration * std::pow(time_1, 2.0);
//		std::cout << "Accel: " << std::fixed << std::setw(6) << std::setprecision(1) << dist_1 << "m during " << std::fixed << std::setw(6) << std::setprecision(2) << time_1 << " sec." << std::endl;

		double time_3 = (std::abs(final_speed) - max_speed)   / -m_acceleration;
//		double dist_3 = std::abs(max_speed)    * time_3 + 1.0/2.0 / -m_acceleration * std::pow(time_3, 2.0);
//		std::cout << "Decel: " << std::fixed << std::setw(6) << std::setprecision(1) << dist_3 << "m during " << std::fixed << std::setw(6) << std::setprecision(2) << time_3 << " sec." << std::endl;

		std::vector<Vt> profile;
		double t = 0.0;
		profile.push_back(Vt(t, initial_speed));
		t += time_1;
		profile.push_back(Vt(t, std::copysign(max_speed, distance)));
		t += time_3;
		profile.push_back(Vt(t, final_speed));
		return profile;
	}
	else // ((dist_1 + dist_3) == std::abs(distance))
	{
		std::vector<Vt> profile;
		double t = 0.0;
		profile.push_back(Vt(t, initial_speed));
		t += time_1;
		profile.push_back(Vt(t, std::copysign(m_speed_max, distance)));
		t += time_3;
		profile.push_back(Vt(t, final_speed));
		return profile;
	}
}
