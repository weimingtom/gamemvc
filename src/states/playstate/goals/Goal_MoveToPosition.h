#ifndef GOAL_MOVE_POS_H
#define GOAL_MOVE_POS_H

#include "Goals/Goal_Composite.h"
#include "2d/Vector2D.h"
#include "../cactormapa.h"
#include "Raven_Goal_Types.h"

class Goal_MoveToPosition: public Goal_Composite < CActorMapa >
{
  private:

    //the position the bot wants to reach
    Vector2D m_vDestination;

  public:

    Goal_MoveToPosition( CActorMapa* pBot,
                         Vector2D pos );

    //the usual suspects
    void Activate();
    int Process();
    void Terminate();

    //this goal is able to accept messages
    bool HandleMessage( const Telegram& msg );

    void Render();

  private:

    int m_iRetries; //TODO Reintentos.
    int m_iLastRetries; // Doble bucle de intentos.

};

#endif
