#include "CIntroState.h"

#include <misc/debug.h>
#include <misc/Interface.h>

#include <MyGame.h>
#include <states/menustate/CMenuState.h>

#include "IntroModel.h"
#include "IntroView.h"
#include "IntroController.h"

void CIntroState::Init( CGameEngine* game ) {

	m_game_ = static_cast<MyGame*>(game);
	m_model = new IntroModel(*m_game_);
	m_view = new IntroView( m_model );
	m_view->initialize(); // Aqui creamos el controlador asociado a la vista.

}

void CIntroState::Cleanup() {

	delete m_view->setController( NULL );
	delete m_view;
	delete m_model;

}

void CIntroState::Pause() {

}

void CIntroState::Resume() {

}

void CIntroState::HandleEvents() {

    if ( m_game_->interface().input() ) {
        m_model->setEnd( IntroModel::QUIT );
    }
    switch ( m_model->getEnd() ) {

        case IntroModel::QUIT:
            m_game_->Quit();
            break;

        case IntroModel::MENU:
            m_game_->ChangeState( &MenuState );
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

}
