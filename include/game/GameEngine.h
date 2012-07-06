#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "gamestate.hpp"

class TiXmlElement;

class GameEngine
{
  public:

    /*!
     * @brief Inicializacion del juego.
     *
     */

    void ChangeState( GameState* state );
    void PushState( GameState* state );
    void PopState();

    void HandleEvents();
    void Update();
    void Draw();

    bool Running()
    {
      return m_running;
    }
    void Quit()
    {
      m_running = false;
    }

  protected:

    virtual void Init();
    virtual void Cleanup()=0;

  private:

    // the stack of states
    std::vector < GameState* > states;
    bool m_running;

};

#endif
