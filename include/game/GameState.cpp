/*
 * GameState.cpp
 *
 *  Created on: 12/08/2010
 *      Author: Rafael Ugalde Beriain
 */
#include "gamestate.hpp"

#include "GameEngine.h"

void GameState::ChangeState( GameEngine* game,
                             GameState* state )
{
  game->ChangeState( state );
}
