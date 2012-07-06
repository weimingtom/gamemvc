#ifndef GOAL_WANDER_H
#define GOAL_WANDER_H

//-----------------------------------------------------------------------------
//
//  Name:   Goal_Wander.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Causes a bot to wander until terminated
//-----------------------------------------------------------------------------
#include "Goals/Goal.h"
#include "Raven_Goal_Types.h"
#include "../cactormapa.h"

class Goal_Wander: public Goal < CActorMapa >
{
  private:

  public:

    Goal_Wander( CActorMapa* pBot ) :
        Goal < CActorMapa >( pBot,
                             goal_wander )
    {
    }

    void Activate();

    int Process();

    void Terminate();
};

#endif
