#include "CIntroState.h"

#include <misc/debug.h>

#include <MyGame.h>
#include <states/menustate/CMenuState.h>

#include "IntroModel.h"
#include "IntroView.h"
#include "IntroController.h"

void CIntroState::Init() {

	m_model = new IntroModel();
	m_view = new IntroView( m_model );
	m_view->initialize(); // Aqui creamos el controlador asociado a la vista.

//	LAPP_ <<	"CIntroState Init";

}

void CIntroState::Cleanup() {

	delete m_view->setController( NULL );
	delete m_view;
	delete m_model;

//	LAPP_ <<	"CIntroState Cleanup";

}

void CIntroState::Pause() {

//	LAPP_ <<	"CIntroState Pause";

}

void CIntroState::Resume() {

//	LAPP_ <<	"CIntroState Resume";

}

void CIntroState::HandleEvents() {

	SDL_Event event;

	while ( SDL_PollEvent( &event ) ) {

		if ( event.type == SDL_QUIT )
			m_model->setEnd( IntroModel::QUIT );
		else
			game.getInput().pushInput( event );
	}
	game.getGui().logic();
	switch ( m_model->getEnd() ) {

		case IntroModel::QUIT:
			game.Quit();
		break;

		case IntroModel::MENU:
			game.ChangeState( &MenuState );
		break;

		default:
		break;
	}

}

void CIntroState::Update() {

	m_model->Update();

}

void CIntroState::Draw() {

	m_model->notify();
	SDL_Flip( game.getScreen() );

}
