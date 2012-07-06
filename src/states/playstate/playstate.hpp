/*
 * PlayState.h
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <game/GameEngine.h>
#include <misc/singleton.hpp>

class GameEngine;
class MyGame;

class PlayModel;
class PlayView;
class PlayController;

#define playstate Singleton < PlayState >::Instance()

class PlayState: public GameState
{
  public:

    virtual ~PlayState();

    void Init( GameEngine* game );
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents();
    void Update();
    void Draw();

  private:

    MyGame* m_game_;
    PlayModel* m_model;
    PlayView * m_view;

    long m_lLastTick; //! Last ticks....

};

#endif /* CPLAYSTATE_H_ */
