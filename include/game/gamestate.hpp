/*
 * gamestate.hpp
 *
 *  Created on: 22/08/2011
 *      Author: 79481180
 */

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

class GameEngine;

class GameState
{
  public:

    virtual void Init( GameEngine* game ) = 0;
    virtual void Cleanup() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    void ChangeState( GameEngine* game,
                      GameState* state );

  protected:
    GameState()
    {
    }

};

#endif /* GAMESTATE_HPP_ */
