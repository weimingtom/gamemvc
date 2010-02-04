/*
 * Game.cpp
 *
 *  Created on: 01/01/2010
 *      Author: uberiain
 */

#include "Game.h"

#include <windows.h>

#include <IsoHex/MapFactory.hpp>

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayController.h"

void Game::Init() {

	InitSDL();
	InitGuichan();

	m_model = new PlayModel();
	m_view = new PlayView( m_model );
	m_view->initialize();

}

void Game::run() {
	bool running = true;

	while ( running ) {
		while ( SDL_PollEvent( &event ) ) {
			if ( event.type == SDL_KEYDOWN ) {
				if ( event.key.keysym.sym == SDLK_ESCAPE ) {
					running = false;
				}

			} else if ( event.type == SDL_QUIT ) {
				running = false;
			}

			input->pushInput( event );
		}

		gui->logic();
		gui->draw();

		m_model->notify(); // Pintar el mapa.....

		SDL_Flip(m_screen_);

	}
}

void Game::End() {

	delete gui;
	delete font;
	delete input;
	delete graphics;
	delete imageLoader;

	SDL_Quit();
}
gcn::Gui& Game::getGui() {

	return *gui;

}

//-------------------------------------------------------------------------------
//
// Procedimientos privados
//
//-------------------------------------------------------------------------------
void Game::InitSDL() {

	SDL_Init( SDL_INIT_VIDEO);
	int flags = SDL_SWSURFACE;
	m_screen_ = SDL_SetVideoMode( 1024, 768, 0, flags );

	SDL_EnableUNICODE( 1 );
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

}
void Game::InitGuichan() {

	imageLoader = new gcn::SDLImageLoader();
	gcn::Image::setImageLoader( imageLoader );
	graphics = new gcn::SDLGraphics();
	graphics->setTarget( m_screen_ );
	input = new gcn::SDLInput();

	font
			= new gcn::ImageFont(	"fixedfont.bmp",
									" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" );
	gcn::Widget::setGlobalFont( font );

	gui = new gcn::Gui();
	gui->setGraphics( graphics );
	gui->setInput( input );

}
