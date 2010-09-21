/*
 * Game.h
 *
 *  Created on: 01/01/2010
 *      Author: uberiain
 */

#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <guichan.hpp>
#include <guichan/sdl.hpp>

#include <misc/singleton.hpp>

#include <IsoHex/MouseMap.hpp>
#include <IsoHex/IMap.hpp>

#include "Tile.h"


class PlayModel;
class PlayView;
class PlayController;

#define game Singleton < Game >::Instance()

class Game {
public:

	Game(){};

	void Init();
	void run();
	void End();

	virtual ~Game(){};

	virtual gcn::Gui& getGui();

private:

	void InitSDL();
	void InitGuichan();



	SDL_Surface*	m_screen_;

	SDL_Event event;

	gcn::SDLImageLoader* imageLoader;
	gcn::SDLGraphics* graphics;
	gcn::SDLInput* input;
	gcn::ImageFont* font;
	gcn::Gui* gui;

	PlayModel* m_model;
	PlayView * m_view;

};

#endif /* GAME_H_ */
