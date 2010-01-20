/*
 * MyGame.h
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */

#ifndef MYGAME_H_
#define MYGAME_H_

#include <string>
#include <map>
#include <utility>
#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <boost/utility.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <game/CGameEngine.h>
#include <misc/singleton.hpp>

namespace pt = boost::property_tree;

class SDL_Surface;

class MyGame: public CGameEngine
{
public:
	enum Resolution
	{

		SMALL = 0,
		MEDIUM,
		BIG

	};

	MyGame();

	void Init( const std::string& config );
	void Cleanup();

	gcn::Gui& getGui() const;
	gcn::SDLInput& getInput() const;
	void flip();
	void changeResolution( std::pair < std::string, bool > res );

	const std::pair < std::string, bool > getResolution() const;
	int getPosResolution();

private:

	std::map < std::string, Resolution > m_screen_resolution;
	std::pair < std::string, bool > m_default_resolution_;
	gcn::Gui* gui;
	gcn::ImageFont* font;
	gcn::SDLInput* input;
	gcn::SDLGraphics* graphics;
	gcn::SDLImageLoader* imageLoader;
	SDL_Surface* m_screen_;
	pt::ptree pt;

	/*
	 * Procedimientos privados.
	 */
	void InitParam( const std::string& config );
	void InitSDL();
	void InitLua();

};

#endif /* MYGAME_H_ */
