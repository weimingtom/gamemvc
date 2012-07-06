#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <game/gamestate.hpp>
#include <misc/singleton.hpp>

class MenuModel;
class MenuView;
namespace gcn {
  class Widget;
}
class GameEngine;
class MyGame;

#define menustate Singleton < MenuState >::Instance()

class MenuState: public GameState
{
  public:

    virtual ~MenuState();

    void Init( GameEngine* game );
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents();
    void Update();
    void Draw();

  private:

    MyGame* game_;
    gcn::Widget* top_;
    MenuModel* model_;
    MenuView * view_;

};

#endif /* MENUSTATE_H */
