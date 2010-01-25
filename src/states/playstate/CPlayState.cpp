/*
 * CPlayState.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "CPlayState.h"

#include <SDL/SDL.h>

#include <misc/debug.h>
#include <misc/Interface.h>

#include <MyGame.h>

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayController.h"

void CPlayState::Init( CGameEngine* game ) {

	m_game_ = static_cast < MyGame* > ( game );
	m_model = new PlayModel(*m_game_);
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


	if (m_game_->interface().input()){
		m_model->setEnd( PlayModel::QUIT );
	}
	switch ( m_model->getEnd() ) {

		case PlayModel::QUIT:
			m_game_->Quit();
			break;

		case PlayModel::MENU:
			m_game_->PopState();
			break;

		default:
			break;
	}

}

void CPlayState::Update() {

	long iElapsedTicks = SDL_GetTicks() - m_lLastTick;
	m_lLastTick = SDL_GetTicks();
	m_model->Update( iElapsedTicks );

}

void CPlayState::Draw() {

	m_model->notify();

}
