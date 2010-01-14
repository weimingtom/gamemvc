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

}

void CPlayState::Cleanup() {

	delete m_view->setController( NULL );
	delete m_view;
	delete m_model;

}

void CPlayState::Pause() {

}

void CPlayState::Resume() {

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

	long iElapsedTicks = SDL_GetTicks() - m_lLastTick;
	m_lLastTick = SDL_GetTicks();
	m_model->Update(iElapsedTicks);

}

void CPlayState::Draw() {

	m_model->notify();
	SDL_Flip( game.getScreen() );

}
