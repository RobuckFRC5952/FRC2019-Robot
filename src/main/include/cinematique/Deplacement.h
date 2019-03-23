/*
 * Deplacement.h
 *
 *  Created on: Jan. 15, 2019
 *      Author: Philippe Brais
 */

/// \file Deplacement.h
/// \brief Générer le profile de vitesse en fonction d'un déplacement désiré.

#ifndef SRC_CINEMATIQUE_DEPLACEMENT_H_
#define SRC_CINEMATIQUE_DEPLACEMENT_H_

#include <vector>

#include "Cinematique.h"


/** Générer le profil de vitesse en fonction d'un déplacement désiré.
 *
 * Cette classe calcule en fonction des paramètres suivants:
 * - Accélération (L/s²),
 * - Vitesse maximale (L/s),
 * - Vitesse initiale (en général 0.0) (L/s),
 * - Vitesse finale (en général 0.0) (L/s), puis
 * - Déplacement (L)
 *
 * Elle calcule le profil de vitesse suivant:
 *
 *       (L/s) ^
 *             |
 *        Vmax |        --------
 *             |       /        \
 *             |      /          \
 *             |     /            \___ V_Final
 *      V_Init | ___/
 *         0.0 +----+---+-------+--+----> t (s)
 *                  0   1       2  3
 *
 * Cette courbe peut être décomposée en quatre segments / phases:
 *
 * - t<SUB>0</SUB>: Temps zéro avec une vitesse initiale v<SUB>0</SUB>.
 * - t<SUB>1</SUB>: Accélération à la vitesse maximale (ou moins) v<SUB>1</SUB>.
 * - t<SUB>2</SUB>: Maintien de la vitesse maximale (ou moins) v<SUB>2</SUB> == v<SUB>1</SUB>.
 * - t<SUB>3</SUB>: Décélération à la vitesse finale v<SUB>3</SUB>.
 */
class Deplacement {
public:
	Deplacement();
	virtual ~Deplacement();

	/** Changer l'accélération du générateur de profil de vitesse.
	 *
	 * \param acceleration Accélération entre \htmlonly ]0.0, ∞] \endhtmlonly \latexonly ]0.0, inf] \endlatexonly
	 *
	 * \note L'accélération est par défaut infinie.
	 */
	void setAcceleration(double acceleration);

	/** Changer la vitesse maximale du générateur de profile de vitesse.
	 *
	 * \param max_speed Vitesse maximale supportée par le sous-système.
	 *
	 * \warning La vitesse maximale est par défaut 0.0.  Ceci veut dire qu'un
	 * profil de vitesse aura un temps de maintien (t<SUB>2</SUB>) infini s'il
	 * n'est pas changé.
	 */
	void setSpeedMax(double max_speed);

	/** Calculateur d'un profil de vitesse.
	 *
	 * Cette méthode calcule ce profil de vitesse pour que la surface sous la
	 * courbe soit la distance à parcourir.
	 *
	 * En fonction des paramètres, il est possible qu'il n'y ait pas un temps
	 * de maintien de la vitesse maximale.
	 *
	 * Il est aussi possible que la vitesse maximale ne soit pas atteinte si le
	 * déplacement est petit.
	 *
	 *       (L/s) ^
	 *             |
	 *        Vmax | - - - - - -
	 *             |
	 *             |      /\
	 *             |     /  \___ V_Final
	 *      V_Init | ___/
	 *         0.0 +----+--+-+----> t (s)
	 *                  0  1 3
	 *
	 * \note La distance et les vitesses peuvent aussi être négatives.
	 *
	 * Exemple d'utilisation:
	 *
	 * \code{.cpp}
	 * double acceleration =  1.0;
	 * double max_speed =    10.0;
	 * double distance =    200.0;
	 * double initial_speed = 0.0;
	 * double final_speed   = 0.0;
	 *
	 * Deplacement d;
	 * d.setSpeedMaxSpeed(max_speed);
	 * d.setAcceleration(acceleration);
	 * std::vector<Vt> profile = d.getSpeedProfile(distance, initial_speed, final_speed);
	 * \endcode
	 *
	 * \param distance Distance à parcourir
	 * \param initial_speed Vitesse initiale
	 * \param final_speed Vitesse finale
	 *
	 * \return Un ensemble de points, par exemple
	 *
	 *     profile =
	 *      0.0 L/s à  0.0 s (t0)
	 *     10.0 L/s à 10.0 s (t1)
	 *     10.0 L/s à 15.0 s (t2)
	 *      0.0 L/s à 25.0 s (t3)
	 *
	 * \exception std::range_error
	 * Cette méthode peut lancer des exceptions si:
	 * - Les vitesses initiale et finale ne sont pas limitées entre les vitesses maximales.
	 * - Les vitesses initiale et finale ne conservent pas la même direction.
	 * - Les vitesses initiale et finale n'ont pas le même signe que la distance à parcourir.
	 * - La vitesse finale n'est pas atteignable.
	 */
	std::vector<Vt> getSpeedProfile(double distance, double initial_speed = 0.0, double final_speed = 0.0) const;

private:
	/// Accélération du moteur (L/s²).
	double m_acceleration;

	/// Vitesse maximal du moteur (L/c).
	double m_speed_max;
};

#endif /* SRC_CINEMATIQUE_DEPLACEMENT_H_ */
