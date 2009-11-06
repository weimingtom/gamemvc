#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <game/gamestate.h>
#include <misc/Singleton.hpp>

#define IntroState Singleton < CIntroState >::Instance()

class IntroModel;
class IntroView;

class CIntroState:	public CGameState
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

	IntroModel* m_model;
	IntroView* m_view;

};

#endif

