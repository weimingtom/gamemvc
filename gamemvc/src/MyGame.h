/*
 * MyGame.h
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */

#ifndef MYGAME_H_
#define MYGAME_H_

#include <string>
#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <boost/utility.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <game/CGameEngine.h>
#include <misc/Singleton.hpp>

#include "CParam.h"

namespace pt = boost::property_tree;

#define game Singleton < MyGame >::instance()

class MyGame:	public CGameEngine
{
public:

	void Init( const std::string config );
	void Cleanup();

	gcn::Gui& 		getGui() const;
	gcn::SDLInput& 	getInput() const;
	SDL_Surface* 	getScreen();

private:

	gcn::Gui* 				gui;
	gcn::ImageFont* 		font;
	gcn::SDLInput* 			input;
	gcn::SDLGraphics* 		graphics;
	gcn::SDLImageLoader* 	imageLoader;
	SDL_Surface* 			screen;
	pt::ptree 				pt;

	/*
	 * Procedimientos privados.
	 */
	void InitParam( const std::string config );
	void InitSDL();

};

#endif /* MYGAME_H_ */
