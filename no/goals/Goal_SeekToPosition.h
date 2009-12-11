#ifndef GOAL_SEEK_TO_POSITION_H
#define GOAL_SEEK_TO_POSITION_H


#include "Goals/Goal.h"
#include "2d/Vector2D.h"
#include "Raven_Goal_Types.h"
#include "../CActorMapa.h"


class Goal_SeekToPosition : public Goal<CActorMapa>
{

public:

  Goal_SeekToPosition(CActorMapa* pBot, Vector2D target);

  //the usual suspects
  void Activate();
  int  Process();
  void Terminate();

  void Render();

private:

  //the position the bot is moving to
  Vector2D  m_vPosition;

  //the approximate time the bot should take to travel the target location
  double     m_dTimeToReachPos;

  //this records the time this goal was activated
  double     m_dStartTime;

  //returns true if a bot gets stuck
  bool      isStuck()const;

};




#endif

