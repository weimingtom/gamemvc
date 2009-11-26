#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <game/gamestate.h>
#include <misc/singleton.hpp>

class MenuModel;
class MenuView;

namespace gcn {
	class Widget;
}

#define MenuState Singleton < CMenuState >::Instance()

class CMenuState:	public CGameState
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

	gcn::Widget*	top;
	MenuModel* 		m_model;
	MenuView * 		m_view;

};

#endif /* MENUSTATE_H */
