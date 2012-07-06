#ifndef GOAL_TRAVERSE_EDGE_H
#define GOAL_TRAVERSE_EDGE_H

#include "Goals/Goal.h"
#include "2d/Vector2D.h"
#include "../cactor_pathplanner.h"
#include "../navigation/PathEdge.h"

class Goal_TraverseEdge: public Goal < CActorMapa >
{
  private:

    //the edge the bot will follow
    PathEdge m_Edge;

    //true if m_Edge is the last in the path.
    bool m_bLastEdgeInPath;

    //the estimated time the bot should take to traverse the edge
    double m_dTimeExpected;

    //this records the time this goal was activated
    double m_dStartTime;

    //returns true if the bot gets stuck
    bool isStuck() const;

  public:

    Goal_TraverseEdge( CActorMapa* pBot,
                       PathEdge edge,
                       bool LastEdge );

    //the usual suspects
    void Activate();
    int Process();
    void Terminate();
    void Render();
};

#endif

