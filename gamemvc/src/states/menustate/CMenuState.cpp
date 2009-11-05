#include "CMenuState.h"

#include <misc/debug.h>

#include <MyGame.h>
#include <states/playstate/CPlayState.h>

#include "MenuModel.h"
#include "MenuView.h"
#include "MenuController.h"



void CMenuState::Init() {

	m_model = new MenuModel();
	m_view = new MenuView( m_model );
	m_view->initialize();

//	LAPP_ <<	"CMenuState Init";

}

void CMenuState::Cleanup() {

	delete m_view->setController( NULL );
	delete m_view;
	delete m_model;

//	LAPP_ <<	"CMenuState Cleanup";

}

void CMenuState::Pause() {

	top = game.getGui().getTop();
//	LAPP_ <<	"CMenuState Pause";

}

void CMenuState::Resume() {

	game.getGui().setTop(top);
	top->requestFocus();
//	LAPP_ <<	"CMenuState Resume";

}

void CMenuState::HandleEvents() {

	SDL_Event event;

	while ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_QUIT )
			m_model->setEnd( MenuModel::QUIT );
		else
			game.getInput().pushInput( event );
	}
	game.getGui().logic();
	switch ( m_model->getEnd() ) {

		case MenuModel::QUIT:
			game.Quit();
		break;

		case MenuModel::PLAY:
			game.PushState( &PlayState );
			m_model->setEnd(MenuModel::CONTINUE);
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
	SDL_Flip( game.getScreen() );

}
