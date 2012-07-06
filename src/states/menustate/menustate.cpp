#include "menustate.h"

#include <misc/debug.h>

#include <mygame.h>
#include <misc/Interface.h>
#include <states/playstate/playstate.hpp>

#include "menumodel.h"
#include "menuview.h"
#include "menucontroller.h"

MenuState::~MenuState()
{

}
void MenuState::Init( GameEngine* game )
{

  game_ = static_cast < MyGame* >( game );
  model_ = new MenuModel( *game_ );
  view_ = new MenuView( model_ );
  view_->Initialize();

}

void MenuState::Cleanup()
{

  delete view_->controller( NULL );
  delete view_;
  delete model_;

}

void MenuState::Pause()
{

  top_ = game_->interface().screen().getTop();

}

void MenuState::Resume()
{

  game_->interface().screen().setTop( top_ );
  top_->requestFocus();

}

void MenuState::HandleEvents()
{

  if ( game_->interface().input() ) {
    model_->setEnd( MenuModel::QUIT );
  }
  switch ( model_->getEnd() )
  {

    case MenuModel::QUIT:
      game_->Quit();
      break;

    case MenuModel::PLAY:
      game_->PushState( &playstate );
      model_->setEnd( MenuModel::CONTINUE );
      break;

    case MenuModel::CHANGERESOLUTION:

      delete view_->controller( NULL );
      delete view_;
      game_->interface().changeScreenResolution( model_->getResolution() );
      view_ = new MenuView( model_ );
      view_->Initialize();
      model_->setEnd( MenuModel::CONTINUE );

      break;
    default:
      break;
  }

}

void MenuState::Update()
{

  model_->Update();

}

void MenuState::Draw()
{

  model_->Notify();

}
