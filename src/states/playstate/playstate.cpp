/*
 * PlayState.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "playstate.hpp"

#include <SDL/SDL.h>

#include <misc/debug.h>
#include <misc/Interface.h>

#include <mygame.h>

#include "playmodel.h"
#include "playview.h"
#include "playcontroller.h"

PlayState::~PlayState()
{

}

void PlayState::Init( GameEngine* game )
{

  m_game_ = static_cast < MyGame* >( game );
  m_model = new PlayModel( *m_game_ );
  m_view = new PlayView( m_model );
  m_view->Initialize();

}

void PlayState::Cleanup()
{

  delete m_view->controller( NULL );
  delete m_view;
  delete m_model;

}

void PlayState::Pause()
{

}

void PlayState::Resume()
{

}

void PlayState::HandleEvents()
{

  if ( m_game_->interface().input() ) {
    m_model->setEnd( PlayModel::QUIT );
  }
  switch ( m_model->getEnd() )
  {

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

void PlayState::Update()
{

  long iElapsedTicks = SDL_GetTicks() - m_lLastTick;
  m_lLastTick = SDL_GetTicks();
  m_model->Update( iElapsedTicks );

}

void PlayState::Draw()
{

  m_model->Notify();

}
