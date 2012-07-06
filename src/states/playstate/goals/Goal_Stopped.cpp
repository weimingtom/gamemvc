#include "Goal_Stopped.h"

#include "Raven_Goal_Types.h"
#include "Messaging/Telegram.h"
#include "Messaging/MessageDispatcher.h"
#include "Time/CrudeTimer.hpp"
#include "../steeringbehaviors.h"

Goal_Stopped::Goal_Stopped( CActorMapa* pBot,
                            double time ) :
    Goal < CActorMapa >( pBot,
                         goal_stopped ), m_dStartTime( Clock.GetCurrentTime() ), m_dWaitTime( time )
{

}
//---------------------------- Activate -------------------------------------
//-----------------------------------------------------------------------------
void Goal_Stopped::Activate()
{

  m_iStatus = active;

  m_pOwner->SetState( "stopped" );
  m_pOwner->SetFrame( 0 );
  m_pOwner->Steering()->SeparationOff();

}
//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Stopped::Process()
{

//      std::cout << "Goal_Stopped::Process" << std::endl;

//if status is inactive, call Activate()
  ActivateIfInactive();
  if ( ( Clock.GetCurrentTime() - m_dStartTime ) < m_dWaitTime )
    m_iStatus = active;
  else
    m_iStatus = failed; // No creo que esto sea correcto, pero para probar

  return m_iStatus;

}
//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Stopped::Terminate()
{
//        std::cout << "Goal_Stopped::Terminate" << std::endl;
}
