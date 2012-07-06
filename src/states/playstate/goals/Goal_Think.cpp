#include "Goal_Think.h"
#include <list>
#include <iostream>
//#include "Graphics/SDLgdi.h"
#include "misc/utils.h"

#include "Goal_MoveToPosition.h"

#include "Raven_Goal_Types.h"

Goal_Think::Goal_Think( CActorMapa* pBot ) :
    Goal_Composite < CActorMapa >( pBot,
                                   goal_think )
{

//	std::cout << "Goal_Think::Goal_Think" << std::endl;
}

//----------------------------- dtor ------------------------------------------
//-----------------------------------------------------------------------------
Goal_Think::~Goal_Think()
{

}

//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_Think::Activate()
{

//	std::cout << "Goal_Think::Activate" << std::endl;

  Arbitrate();
  m_iStatus = active;

}

//------------------------------ Process --------------------------------------
//
//  processes the subgoals
//-----------------------------------------------------------------------------
int Goal_Think::Process()
{

//	std::cout << "Goal_Think::Process" << std::endl;

  ActivateIfInactive();

  int SubgoalStatus = ProcessSubgoals();

  if ( SubgoalStatus == completed || SubgoalStatus == failed ) {

    m_iStatus = inactive;

  } else {

    m_iStatus = SubgoalStatus;

  }

  return m_iStatus;
}

//----------------------------- Update ----------------------------------------
//
//  this method iterates through each goal option to determine which one has
//  the highest desirability.
//-----------------------------------------------------------------------------
void Goal_Think::Arbitrate()
{

//	std::cout << "Goal_Think::Arbitrate" << std::endl;

}

//---------------------------- notPresent --------------------------------------
//
//  returns true if the goal type passed as a parameter is the same as this
//  goal or any of its subgoals
//-----------------------------------------------------------------------------
bool Goal_Think::notPresent( unsigned int GoalType ) const
{
  if ( !m_SubGoals.empty() ) {
    return (unsigned int) m_SubGoals.front()->GetType() != GoalType;
  }

  return true;
}
void Goal_Think::Terminate()
{

}
void Goal_Think::Render()
{
  std::list < Goal < CActorMapa >* >::iterator curG;
  for ( curG = m_SubGoals.begin(); curG != m_SubGoals.end(); ++curG ) {
    ( *curG )->Render();
  }
}

