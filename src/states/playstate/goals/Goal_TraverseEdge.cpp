#include "Goal_TraverseEdge.h"

#include <misc\debug.h>
#include <misc\Log.h>

#include "../cactormapa.h"
#include "Raven_Goal_Types.h"
#include "../steeringbehaviors.h"
#include "Time/CrudeTimer.hpp"
#include "../cactor_pathplanner.h"
#include "../lua/Raven_Scriptor.h"

//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Goal_TraverseEdge::Goal_TraverseEdge( CActorMapa* pBot,
                                      PathEdge edge,
                                      bool LastEdge ) :

    Goal < CActorMapa >( pBot,
                         goal_traverse_edge ), m_Edge( edge ), m_bLastEdgeInPath( LastEdge ), m_dTimeExpected( 0.0 )
{
}

//---------------------------- Activate -------------------------------------
//-----------------------------------------------------------------------------
void Goal_TraverseEdge::Activate()
{
  m_iStatus = active;

  //the edge behavior flag may specify a type of movement that necessitates a
  //change in the bot's max possible speed as it follows this edge
  switch ( m_Edge.Behavior() )
  {

    case NavGraphEdge::swim: {
      m_pOwner->SetMaxSpeed( script->GetDouble( "Bot_MaxSwimmingSpeed" ) );
    }

      break;

    case NavGraphEdge::crawl: {
      m_pOwner->SetMaxSpeed( script->GetDouble( "Bot_MaxCrawlingSpeed" ) );
    }

      break;
  }

  //record the time the bot starts this goal
  m_dStartTime = Clock.GetCurrentTime();

  //calculate the expected time required to reach the this waypoint. This value
  //is used to determine if the bot becomes stuck
  m_dTimeExpected =
      m_pOwner->CalculateTimeToReachPosition( m_Edge.Destination() );

  //factor in a margin of error for any reactive behavior
  static const double MarginOfError = 4.0;

  m_dTimeExpected += MarginOfError;

  //set the steering target
  m_pOwner->Steering()->SetTarget( m_Edge.Destination() );

  //Set the appropriate steering behavior. If this is the last edge in the path
  //the bot should arrive at the position it points to, else it should seek
  if ( m_bLastEdgeInPath ) {
    m_pOwner->Steering()->ArriveOn();
  }

  else {
    m_pOwner->Steering()->SeekOn();
  }
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_TraverseEdge::Process()
{

//	std::cout << "Goal_TraverseEdge::Process" << std::endl;
//	std::cout << " ++ ";
  //if status is inactive, call Activate()
  ActivateIfInactive();

//  Vector2D Estoy = m_pOwner->Pos();
//  Vector2D Voy = m_Edge.Destination();
//	std::cout << "Estoy (" << Estoy.x << "," << Estoy.y << ") Voy (" << Voy.x
//			<< "," << Voy.y << ")" << std::endl;

  //if the bot has become stuck return failure
  if ( isStuck() ) {
    m_iStatus = failed;
  }

  //if the bot has reached the end of the edge return completed
  else {
    if ( m_pOwner->isAtPosition( m_Edge.Destination() ) ) {
      m_iStatus = completed;
    }
  }

  return m_iStatus;
}

//--------------------------- isBotStuck --------------------------------------
//
//  returns true if the bot has taken longer than expected to reach the
//  currently active waypoint
//-----------------------------------------------------------------------------
bool Goal_TraverseEdge::isStuck() const
{
  double TimeTaken = Clock.GetCurrentTime() - m_dStartTime;

  if ( TimeTaken > m_dTimeExpected ) {

    LDBG_( "BOT " << m_pOwner->ID() << " IS STUCK!!" << "[Goal_TraverseEdge]" );

    return true;
  }

  return false;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_TraverseEdge::Terminate()
{
//	std::cout << "Goal_SeekToPosition::Terminate" << std::endl;
  //turn off steering behaviors.
  m_pOwner->Steering()->SeekOff();
  m_pOwner->Steering()->ArriveOff();

  //return max speed back to normal
  m_pOwner->SetMaxSpeed( script->GetDouble( "MaxSpeed" ) );

}

//----------------------------- Render ----------------------------------------
//-----------------------------------------------------------------------------
void Goal_TraverseEdge::Render()
{

  if ( m_iStatus == active ) {
    gdi->SetPenColor( gcn::Color::Blue );
    gdi->LineISO( m_pOwner->Pos(),
                  m_Edge.Destination() );
    //		gdi->GreenBrush();
    gdi->SetPenColor( gcn::Color::Black );
    gdi->CircleISO( m_Edge.Destination(),
                    3 );
  }

}

