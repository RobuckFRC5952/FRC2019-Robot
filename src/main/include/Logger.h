/*
 * Logger.h
 *
 *  Created on: Dec. 30, 2018
 *      Author: Philippe Brais
 */

#ifndef INCLUDE_LOGGER_H_
#define INCLUDE_LOGGER_H_

/// \file Logger.h
/// \brief Fichier pour pouvoir utiliser \b wpi::Logger.
///
/// Le logger de WPI offre une classe et des macros pour logger ou pas selon
/// le niveau spécifié des messages.  Cette classe a besoin d'une fonction
/// qu'on lui fournit: log_func().
///
/// Voici l'utilisation suggérée des macros disponibles:
///
/// | Macro          | Utilisation
/// | -------------- | ----------------------------------------------------------
/// | \c WPI_ERROR   | Les erreurs, e.g., dépasser une limite de l'encodeur, ...
/// | \c WPI_WARNING | Les warnings, e.g. un timeout d'une commande, ...
/// | \c WPI_INFO    | Les noms des commandes et sous-commandes appelées, ...
/// | \c WPI_DEBUG   | Afficher des données, calcules, etc.
/// | \c WPI_DEBUG1  | Afficher des données, calcules, etc. récurrentes.
/// | \c WPI_DEBUG2  | |
/// | \c WPI_DEBUG3  | Tracer l'entrée/sortie des fonctions non récurrentes.
/// | \c WPI_DEBUG4  | Tracer l'entrée/sortie des fonctions récurrentes.


/** La function appelée par \b wpi::Logger.
 *
 * Cette fonction regarde le niveau d'erreur (\c level) et affiche un message
 * en appelant soit:
 * - \c frc::DriverStation::ReportError
 * - \c frc::DriverStation::ReportWarning
 * - \c std::cout
 *
 * Tous les messages imprimés par \c cout affichent aussi le temps depuis que le
 * roboRIO est allumé avec la fonction \b frc::Timer::GetFPGATimestamp().
 *
 * \param[in] level Contient un `enum LogLevel` en fonction de la macro appelée, e.g. \c WPI_INFO, \c WPI_DEBUG, etc.
 * \param[in] file  Imprime la macro `__FILE__`.
 * \param[in] line  Imprime la macro `__LINE__`.
 * \param[in] msg   Votre message avec des opérateurs d'insertion (\c <<) dans
 *                  les macros \c WPI_INFO, \c WPI_DEBUG, etc.
 *
 * \note Cette fonction doit conserver la signature telle que définie par le typedef
 *       \c LogFunc.
 *
 * \sa http://first.wpi.edu/FRC/roborio/release/docs/cpp/classwpi_1_1Logger.html
 *     et aussi http://first.wpi.edu/FRC/roborio/release/docs/cpp/Logger_8h_source.html.
 */
void log_func(unsigned int level, const char* file, unsigned int line, const char* msg);

#endif /* INCLUDE_LOGGER_H_ */
