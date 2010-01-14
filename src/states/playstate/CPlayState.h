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

class MyGame;

class PlayModel;
class PlayView;
class PlayController;

#define PlayState Singleton < CPlayState >::Instance()

class CPlayState: public CGameState
{
public:

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

private:

	PlayModel* m_model;
	PlayView * m_view;

	long m_lLastTick; 	//! Last ticks....


};

#endif /* CPLAYSTATE_H_ */
