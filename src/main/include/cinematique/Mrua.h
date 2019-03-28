/*
 * Mrua.h
 *
 *  Created on: Dec. 16, 2018
 *      Author: Philippe Brais
 */

/// \file Mrua.h
/// \brief Mouvement rectiligne uniformément accéléré.

#ifndef SRC_CINEMATIQUE_MRUA_H_
#define SRC_CINEMATIQUE_MRUA_H_

#include <ostream>

#include <frc/Timer.h>
#include <wpi/raw_ostream.h>


/** Mouvement rectiligne uniformément accéléré.
 *
 * Calculer la vitesse et la position à un temps t en fonction d'une
 * accélération constante.
 *
 * Une fois l'objet construit, on ne peut plus changer l'accélération ni les
 * vitesse et position initiales.
 *
 * \sa [Mouvement rectiligne uniformément accéléré (MRUA)]
 * (https://fr.wikipedia.org/wiki/Cin%C3%A9matique#Mouvement_rectiligne_uniform%C3%A9ment_acc%C3%A9l%C3%A9r%C3%A9_(MRUA))
 */
class Mrua {
public:

	/** Constructeur fournissant l'accélération, et les vitesse et position initiales.
	 *
	 * \note En mettant des '`= 0.0`' aux derniers paramètres, il est possible d'instancier
	 *       l'objet en fournissant simplement l'accélération.
	 */
	Mrua(double acceleration, double initial_speed = 0.0, double initial_position = 0.0);

	/** Méthode pour démarrer le mouvement rectiligne dans le temps.
	 *
	 * Elle démarre tout simplement son timer interne.
	 */
	void Initialize();

	/** Méthode pour chercher l'accélération en cours.
	 */
	double getAcceleration() const;

	/** Méthode pour calculer la vitesse au moment présent.
	 */
	double getIntegratedSpeed() const;

	/** Méthode pour calculer la vitesse au moment \c time.
	 * \param[in] time Temps quelconque
	 */
	double getIntegratedSpeed(double time) const;

	/** Méthode pour calculer la position au moment présent.
	 */
	double getIntegratedPosition() const;

	/** Méthode pour calculer la position au moment \c time.
	 * \param[in] time Temps quelconque
	 */
	double getIntegratedPosition(double time) const;

private:
	/// Accélération constante (L / sec²).
	double const m_acceleration;

	/// Vitesse initiale (L / sec).
	double const m_initial_speed;

	/// Position initiale (L).
	double const m_initial_position;

	/// Évolution du temps.
	frc::Timer m_time;

	/// Définition de \c std::ostream::operator<< en tant que \c friend pour
	/// être capable d'imprimer les variables privées de la classe.
	/// @{
	friend std::ostream & operator<<(std::ostream & os, Mrua const & o);
	friend wpi::raw_ostream & operator<< (wpi::raw_ostream & os, Mrua const & o);
	/// @}
};

#endif /* SRC_CINEMATIQUE_MRUA_H_ */
