#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <game/gamestate.h>
#include <misc/singleton.hpp>

#define IntroState Singleton < CIntroState >::Instance()

class IntroModel;
class IntroView;

class MyGame;
class CGameEngine;

class CIntroState:	public CGameState
{
public:

	void Init( CGameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

private:

	MyGame*		m_game_;
	IntroModel* m_model;
	IntroView* 	m_view;

};

#endif

