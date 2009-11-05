/*
 * CPlayState.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "CPlayState.h"

#include <misc/debug.h>

#include <MyGame.h>

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayController.h"

void CPlayState::Init() {

	m_model = new PlayModel();
	m_view = new PlayView( m_model );
	m_view->initialize();

//	LAPP_ <<	"CPlayState Init";

}

void CPlayState::Cleanup() {

	delete m_view->setController( NULL );
	delete m_view;
	delete m_model;

//	LAPP_ <<	"CPlayState Cleanup";

}

void CPlayState::Pause() {

//	LAPP_ <<	"CPlayState Pause";

}

void CPlayState::Resume() {

//	LAPP_ <<	"CPlayState Resume";

}

void CPlayState::HandleEvents() {

	SDL_Event event;

	while ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_QUIT )
			m_model->setEnd( PlayModel::QUIT );
		else
			game.getInput().pushInput( event );
	}
	game.getGui().logic();
	switch ( m_model->getEnd() ) {

		case PlayModel::QUIT:
			game.Quit();
		break;

		case PlayModel::MENU:
			game.PopState();
		break;

		default:
		break;
	}

}

void CPlayState::Update() {

	m_model->Update();

}

void CPlayState::Draw() {

	m_model->notify();
	SDL_Flip( game.getScreen() );

}
