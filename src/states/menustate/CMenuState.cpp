#include "CMenuState.h"

#include <misc/debug.h>

#include <MyGame.h>
#include <states/playstate/CPlayState.h>

#include "MenuModel.h"
#include "MenuView.h"
#include "MenuController.h"

void CMenuState::Init( CGameEngine* game ) {

	m_game_ = static_cast<MyGame*>(game);
	m_model = new MenuModel(*m_game_);
	m_view = new MenuView( m_model );
	m_view->initialize();

}

void CMenuState::Cleanup() {

	delete m_view->setController( NULL );
	delete m_view;
	delete m_model;

}

void CMenuState::Pause() {

	top = m_game_->getGui().getTop();

}

void CMenuState::Resume() {

	m_game_->getGui().setTop( top );
	top->requestFocus();

}

void CMenuState::HandleEvents() {

	SDL_Event event;

	while ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_QUIT )
			m_model->setEnd( MenuModel::QUIT );
		else
			m_game_->getInput().pushInput( event );
	}
	m_game_->getGui().logic();
	switch ( m_model->getEnd() ) {

		case MenuModel::QUIT:
			m_game_->Quit();
			break;

		case MenuModel::PLAY:
			m_game_->PushState( &PlayState );
			m_model->setEnd( MenuModel::CONTINUE );
			break;

		case MenuModel::CHANGERESOLUTION:

			delete m_view->setController( NULL );
			delete m_view;
			m_game_->changeResolution(	m_model->getResolution());
			m_view = new MenuView( m_model );
			m_view->initialize();
			m_model->setEnd( MenuModel::CONTINUE );

			break;
		default:
			break;
	}

}

void CMenuState::Update() {

	m_model->Update();

}

void CMenuState::Draw() {

	m_model->notify();

}
