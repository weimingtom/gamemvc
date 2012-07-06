#include "GameEngine.h"

#include <iostream>
#include <tinyxml.h>

void GameEngine::Init()
{

  m_running = true;

 }

void GameEngine::Cleanup()
{
  // cleanup the all states
  while ( !states.empty() ) {
    states.back()->Cleanup();
    states.pop_back();
  }
}

void GameEngine::ChangeState( GameState * state )
{
  // cleanup the current state
  if ( !states.empty() ) {
    states.back()->Cleanup();
    states.pop_back();
  }
  // store and init the new state
  states.push_back( state );
  states.back()->Init( this );
}

void GameEngine::PushState( GameState * state )
{
  // pause current state
  if ( !states.empty() ) {
    states.back()->Pause();
  }
  // store and init the new state
  states.push_back( state );
  states.back()->Init( this );
}

void GameEngine::PopState()
{
  // cleanup the current state
  if ( !states.empty() ) {
    states.back()->Cleanup();
    states.pop_back();
  }
  // resume previous state
  if ( !states.empty() ) {
    states.back()->Resume();
  }
}
void GameEngine::HandleEvents()
{
  // let the state handle events
  states.back()->HandleEvents();
}
void GameEngine::Update()
{
  // let the state update the game
  states.back()->Update();
}
void GameEngine::Draw()
{
  // let the state draw the screen
  states.back()->Draw();
}
