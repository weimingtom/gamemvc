#include "introstate.h"

#include <misc/debug.h>
#include <misc/Interface.h>

#include <mygame.h>
#include <states/menustate/menustate.h>

#include "intromodel.h"
#include "introview.h"
#include "introcontroller.h"

IntroState::~IntroState()
{

}

void IntroState::Init( GameEngine* game )
{

  game_ = static_cast < MyGame* >( game );
  model_ = new IntroModel( *game_ );
  view_ = new IntroView( model_ );
  view_->Initialize(); // Aqui creamos el controlador asociado a la vista.

}

void IntroState::Cleanup()
{

  delete view_->controller( NULL );
  delete view_;
  delete model_;

}

void IntroState::Pause()
{

}

void IntroState::Resume()
{

}

void IntroState::HandleEvents()
{

  if ( game_->interface().input() ) {
    model_->endtype( IntroModel::QUIT );
  }

  switch ( model_->endtype() )
  {

    case IntroModel::CONTINUE:
      break;

    case IntroModel::MENU:
      ChangeState( game_,
                   &menustate );
      break;

    case IntroModel::QUIT:
      game_->Quit();
      break;

  }

}

void IntroState::Update()
{

  model_->Update();

}

void IntroState::Draw()
{

  model_->Notify();

}
