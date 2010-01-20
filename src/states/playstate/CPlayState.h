/*
 * CPlayState.h
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#ifndef CPLAYSTATE_H_
#define CPLAYSTATE_H_

#include <game/CGameEngine.h>
#include <misc/singleton.hpp>

class CGameEngine;
class MyGame;

class PlayModel;
class PlayView;
class PlayController;

#define PlayState Singleton < CPlayState >::Instance()

class CPlayState: public CGameState
{
public:

	void Init(CGameEngine* game  );
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

private:

	MyGame*		m_game_;
	PlayModel*  m_model;
	PlayView *  m_view;

	long m_lLastTick; //! Last ticks....


};

#endif /* CPLAYSTATE_H_ */
