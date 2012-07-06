#ifndef GOAL_FOLLOWPATH_H
#define GOAL_FOLLOWPATH_H

//-----------------------------------------------------------------------------
//
//  Name:   Goal_FollowPath.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:
//-----------------------------------------------------------------------------
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../cactormapa.h"
#include "../cactor_pathplanner.h"
#include "../navigation/PathEdge.h"

class Goal_FollowPath: public Goal_Composite < CActorMapa >
{
  private:

    //a local copy of the path returned by the path planner
    std::list < PathEdge > m_Path;

  public:

    Goal_FollowPath( CActorMapa* pBot,
                     std::list < PathEdge > path );

    //the usual suspects
    void Activate();
    int Process();
    void Render();
    void Terminate()
    {
    }
};

#endif

