/*
 * Cinematique.h
 *
 *  Created on: Jan. 16, 2019
 *      Author: Philippe Brais
 */

/// \file Cinematique.h
/// \brief Ensemble de structures et fonctions se rapportant à la cinématique.

#ifndef INCLUDE_CINEMATIQUE_H_
#define INCLUDE_CINEMATIQUE_H_

#include <sstream>
#include <vector>


/** Structure pour conserver le temps et la vitesse.
 */
struct Vt
{
	/// Constructeur
	Vt(double time = 0.0, double speed = 0.0) : m_time(time), m_speed(speed) {}

	double const m_time;  ///< Durée depuis le début du mouvement.
	double const m_speed; ///< Vitesse.
};


/** Fonction pour imprimer le profil
 *
 * \param profile Vecteur de structure Vt.
 */
std::ostringstream print_vt_profile(std::vector<Vt> const & profile);

#endif /* INCLUDE_CINEMATIQUE_H_ */
