/*
 * Quadratique.h
 *
 *  Created on: Jan. 17, 2019
 *      Author: Philippe Brais
 */

/// \file Quadratique.h
/// \brief Calculs mathématiques pour trouver les racines d'une équation du
///        second degré

#ifndef SRC_CINEMATIQUE_QUADRATIQUE_H_
#define SRC_CINEMATIQUE_QUADRATIQUE_H_

#include <vector>

/** Résoudre une équation de second degré.
 *
 * \sa [https://fr.wikipedia.org/wiki/Équation_du_second_degré](https://fr.wikipedia.org/wiki/%C3%89quation_du_second_degr%C3%A9)
 */
class Quadratique final
{
public:
	/** Constructeur
	 *
	 * \param a, b, c Coefficients avec \htmlonly a ≠ 0.0 \endhtmlonly \latexonly a <> 0.0 \endlatexonly.
	 */
	Quadratique(double a, double b, double c);
	~Quadratique();

	/** Retourner le discriminant
	 *
	 * \return Retourner \htmlonly Δ = b² − 4ac \endhtmlonly \latexonly le discriminant \endlatexonly
	 */
	double getDiscriminant() const;

	/** Retourner la racine double, ou les deux racines.
	 *
	 * \return Vecteur de racines.
	 */
	std::vector<double> getRoots() const;

private:
	///
	/// \name Coefficients de l'équation quadratique, avec 'a' différent de zéro.
	///
	/// @{
	const double m_a;
	const double m_b;
	const double m_c;
	/// @}
};

#endif /* SRC_CINEMATIQUE_QUADRATIQUE_H_ */
