#include "Goal_SeekToPosition.h"

#include <misc\debug.h>
#include <misc\Log.h>

#include "../cactormapa.h"
#include "../steeringbehaviors.h"
#include "Time/CrudeTimer.hpp"
#include "../cactor_pathplanner.h"

//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Goal_SeekToPosition::Goal_SeekToPosition( CActorMapa* pBot,
                                          Vector2D target ) :

    Goal < CActorMapa >( pBot,
                         goal_seek_to_position ), m_vPosition( target ), m_dTimeToReachPos( 0.0 )
{
}

//---------------------------- Activate -------------------------------------
//-----------------------------------------------------------------------------
void Goal_SeekToPosition::Activate()
{
  m_iStatus = active;

  //record the time the bot starts this goal
  m_dStartTime = Clock.GetCurrentTime();

  //This value is used to determine if the bot becomes stuck
  m_dTimeToReachPos = m_pOwner->CalculateTimeToReachPosition( m_vPosition );

  //factor in a margin of error for any reactive behavior
  const double MarginOfError = 4.0; // !! Era 1.0

  m_dTimeToReachPos += MarginOfError;

  m_pOwner->Steering()->SetTarget( m_vPosition );

  m_pOwner->Steering()->SeekOn();

  m_pOwner->SetDir( "S" );
  m_pOwner->SetState( "walking" );
  m_pOwner->SetFrame( 0 );

}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_SeekToPosition::Process()
{
//	std::cout << "Goal_SeekToPosition::Process" << std::endl;
//	std::cout << " ++ ";
  //if status is inactive, call Activate()
  ActivateIfInactive();
//  Vector2D Estoy = m_pOwner->Pos();
//  Vector2D Voy = m_vPosition;
//	std::cout << "Estoy (" << Estoy.x << "," << Estoy.y << ") Voy (" << Voy.x
//			<< "," << Voy.y << ")" << std::endl;
  //test to see if the bot has become stuck
  if ( isStuck() ) {
    m_iStatus = failed;
  }
  //test to see if the bot has reached the waypoint. If so terminate the goal
  else {

    if ( m_pOwner->isAtPosition( m_vPosition ) ) {
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
bool Goal_SeekToPosition::isStuck() const
{

  double TimeTaken = Clock.GetCurrentTime() - m_dStartTime;

  if ( TimeTaken > m_dTimeToReachPos ) {

    LDBG_( "BOT " << m_pOwner->ID() << " IS STUCK!!" );

    return true;
  }

  return false;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_SeekToPosition::Terminate()
{
//	std::cout << "Goal_SeekToPosition::Terminate" << std::endl;
  m_pOwner->Steering()->SeekOff();
  m_pOwner->Steering()->ArriveOff();

  m_iStatus = completed;
}

//----------------------------- Render ----------------------------------------
//-----------------------------------------------------------------------------
void Goal_SeekToPosition::Render()
{

  if ( m_iStatus == active ) {
    //    gdi->GreenBrush();
    gdi->SetPenColor( gcn::Color::Red );
    gdi->CircleISO( m_vPosition,
                    3 );
  }

  else if ( m_iStatus == inactive ) {
    //   gdi->RedBrush();
    gdi->SetPenColor( gcn::Color::Red );
    gdi->CircleISO( m_vPosition,
                    3 );
  }

}

