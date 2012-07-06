#include <luabind/luabind.hpp>
using namespace luabind;

#include "Goal_MoveToPosition.h"
#include "../cactormapa.h"
#include "../cactor_pathplanner.h"
#include "../steeringbehaviors.h"
#include "Messaging/Telegram.h"
#include "Messaging/MessageDispatcher.h"
#include "Lua/CLuaManager.h"

#include "Goal_SeekToPosition.h"
#include "Goal_FollowPath.h"
#include "Goal_Stopped.h"

//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Goal_MoveToPosition::Goal_MoveToPosition( CActorMapa* pBot,
                                          Vector2D pos ) :

    Goal_Composite < CActorMapa >( pBot,
                                   goal_move_to_position ), m_vDestination( pos ), m_iRetries( 0 ), m_iLastRetries( 0 )
{
}
//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_MoveToPosition::Activate()
{
  m_iStatus = active;

  //make sure the subgoal list is clear.
  RemoveAllSubgoals();

  m_pOwner->Steering()->SeparationOn(); // Nos vamos a mover... ( Para el pathfinder ).

  static const int maxRetries = 3;
  static const int maxLastRetries = 2;

  m_iRetries++; //TODO Colisiones .....
  if ( m_iRetries < maxRetries ) {

    //requests a path to the target position from the path planner. Because, for
    //demonstration purposes, the Raven path planner uses time-slicing when
    //processing the path requests the bot may have to wait a few update cycles
    //before a path is calculated. Consequently, for appearances sake, it just
    //seeks directly to the target position whilst it's awaiting notification
    //that the path planning request has succeeded/failed
//		std::cout << "Get path";
//		std::cout << " From : " << m_pOwner->Pos();
//		std::cout << " , ";
//		std::cout << " To : " << m_vDestination;
//		std::cout << std::endl;
    if ( m_pOwner->GetPathPlanner()->RequestPathToPosition( m_vDestination ) ) {

      AddSubgoal( new Goal_SeekToPosition( m_pOwner,
                                           m_vDestination ) );

    }
    m_pOwner->SetDir( m_pOwner->isHeadingAt() );
    m_pOwner->SetState( "walking" );
    m_pOwner->SetFrame( 0 );

  } else {

    // Esperamos un poco y replanteamos....?
    ++m_iLastRetries;
    if ( m_iLastRetries < maxLastRetries ) {

      AddSubgoal( new Goal_Stopped( m_pOwner,
                                    0.5 ) );
      m_iRetries = 0; // Reintentar de nuevo?.

    } else {

      m_pOwner->SetState( "stopped" );
      m_pOwner->SetFrame( 0 );
      m_pOwner->Steering()->SeparationOff();
      m_iStatus = failed;

    }
  }

}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_MoveToPosition::Process()
{
//	std::cout << "Goal_MoveToPosition::Process" << std::endl;
//	std::cout << " ++ ";
  //if status is inactive, call Activate()
  ActivateIfInactive();

  m_pOwner->SetDir( m_pOwner->isHeadingAt() );

  //process the subgoals
  m_iStatus = ProcessSubgoals();

//	std::cout << "m_iStatus ---> " << m_iStatus << std::endl;

  //if any of the subgoals have failed then this goal re-plans
  ReactivateIfFailed();

  return m_iStatus;
}
void Goal_MoveToPosition::Terminate()
{

  m_pOwner->SetState( "stopped" );
  m_pOwner->SetFrame( 0 );
  m_pOwner->Steering()->SeparationOff();

}
//---------------------------- HandleMessage ----------------------------------
//-----------------------------------------------------------------------------
bool Goal_MoveToPosition::HandleMessage( const Telegram& msg )
{
  //first, pass the message down the goal hierarchy
  bool bHandled = ForwardMessageToFrontMostSubgoal( msg );

  //if the msg was not handled, test to see if this goal can handle it
  if ( bHandled == false ) {

    switch ( msg.Msg )
    {
      case CActorMapa::Msg_PathReady:

        //clear any existing goals
        RemoveAllSubgoals();

        AddSubgoal( new Goal_FollowPath( m_pOwner,
                                         m_pOwner->GetPathPlanner()->GetPath() ) );

        return true; //msg handled

      case CActorMapa::Msg_NoPathAvailable:

        m_iStatus = failed;

        return true; //msg handled

      default:
        return false;
    }

  }

  //handled by subgoals
  return true;
}

//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void Goal_MoveToPosition::Render()
{

  //forward the request to the subgoals
  Goal_Composite < CActorMapa >::Render();

  //draw a bullseye
  gdi->SetPenColor( gcn::Color::Black );
  //	gdi->BlueBrush();
  gdi->CircleISO( m_vDestination,
                  6 );
  //	gdi->RedBrush();
  gdi->SetPenColor( gcn::Color::Red );
  gdi->CircleISO( m_vDestination,
                  4 );
  //	gdi->YellowBrush();
  gdi->SetPenColor( gcn::Color::Yellow );
  gdi->CircleISO( m_vDestination,
                  2 );

}

