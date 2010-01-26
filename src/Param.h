/*
 * Param.h
 *
 *  Created on: 25/01/2010
 *      Author: uberiain
 */

#ifndef PARAM_H_
#define PARAM_H_

#include <string>

class Param {
public:
	Param(const std::string& config);
	virtual ~Param();

	struct screen {

		std::string resolution; // Resolucion pantalla.
		bool full; // Fullscreen.
		std::string icon; // Icono del programa.
		std::string font; // Font por defecto guichan.

	} screen;

	std::string gamedata; // Fichero datos iniciales del game.
	std::string lua; // Fichero carga inicial Lua.

};

#endif /* PARAM_H_ */
