#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <game/CGameEngine.h>
#include <misc/Singleton.hpp>

class MyGame;

class MenuModel;
class MenuView;
class MenuController;
namespace gcn {
	class Widget;
}

#define MenuState Singleton < CMenuState >::instance()

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
