/*
 * Quadratique.cpp
 *
 *  Created on: Jan. 17, 2019
 *      Author: Philippe Brais
 */

#include "Cinematique/Quadratique.h"

#include <cmath>
#include <stdexcept>

Quadratique::Quadratique(double a, double b, double c)
: m_a(a)
, m_b(b)
, m_c(c)
{
}

Quadratique::~Quadratique() {
}

double Quadratique::getDiscriminant() const
{
	return m_b*m_b - 4.0*m_a*m_c;
}


std::vector<double> Quadratique::getRoots() const
{
	if (m_a == 0.0)
	{
		throw std::runtime_error("Le coefficient 'a' doit être différent de 0.0");
	}

	std::vector<double> racines;
	double delta = getDiscriminant();
	if (delta > 0.0)
	{
		racines.push_back((-m_b + std::sqrt(delta)) / (2.0 * m_a));
		racines.push_back((-m_b - std::sqrt(delta)) / (2.0 * m_a));
	}
	else if (delta == 0.0)	// TODO Ajouter une tolérance
	{
		// Racine double
		racines.push_back(-m_b / (2.0 * m_a));
	}
	else // (delta < 0.0)
	{
		throw std::runtime_error("Le discriminant est négatif.  Cette classe ne support pas les nombres complexes.");
	}
	return racines;
}
