/*
 * CParam.h
 *
 *  Created on: 03/09/2009
 *      Author: 79481180
 */

#ifndef CPARAM_H_
#define CPARAM_H_

#include <boost/utility.hpp>

#include <misc/singleton.hpp>

#define param Singleton < CParam >::Instance()

struct CParam
{

	struct screen
	{

		std::string 	resolution;
		bool 	full; // Fullscreen.

	} screen;

	std::string gamedata; 	// Fichero datos iniciales del game.
	std::string lua;		// Fichero carga inicial Lua.

};

#endif /* CPARAM_H_ */
