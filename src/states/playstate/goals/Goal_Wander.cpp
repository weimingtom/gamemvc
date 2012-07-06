#include "Goal_Wander.h"

#include <iostream>

#include "../cactormapa.h"
#include "../steeringbehaviors.h"

//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------
void Goal_Wander::Activate()
{

//	std::cout << "Goal_Wander::Goal_Wander" << std::endl;

  m_iStatus = active;

  m_pOwner->SetDir( m_pOwner->isHeadingAt() );
  m_pOwner->SetState( "walking" );
  m_pOwner->SetFrame( 0 );

  m_pOwner->Steering()->SeparationOn();
  m_pOwner->Steering()->WanderOn();
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Wander::Process()
{

//	std::cout << "Goal_Wander::Process" << std::endl;

//if status is inactive, call Activate()
  ActivateIfInactive();

  m_pOwner->SetDir( m_pOwner->isHeadingAt() );

  return m_iStatus;

}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Wander::Terminate()
{

//	std::cout << "Goal_Wander::Terminate" << std::endl;

  m_pOwner->Steering()->WanderOff();
  m_pOwner->Steering()->SeparationOff();
}

