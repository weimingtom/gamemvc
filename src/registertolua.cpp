/*
 * RegisterToLua.cpp
 *
 *  Created on: 04-ago-2008
 *      Author: Rafael Ugalde Beriain
 */
#include "registertolua.h"

#include "Messaging/Telegram.h"
#include "Messaging/MessageDispatcher.h"
#include "Time/CrudeTimer.hpp"
#include "game/BaseGameEntity.h"
#include "game/MovingEntity.h"
#include "2d/Vector2D.h"
#include "states/playstate/cactormapa.h"
#include "states/playstate/cactormapa_wrapper.h"
#include "states/playstate/playmodel.h"
#include "states/playstate/steeringbehaviors.h"
#include "states/playstate/cactor_pathplanner.h"

#include <Goals/Goal.h>
#include <Goals/Goal_Composite.h>

#include "states/playstate/goals/Goal_Think.h"
#include "states/playstate/goals/Goal_Think_wrapper.h"
#include "states/playstate/goals/Goal_Wander.h"
#include "states/playstate/goals/Goal_Wander_wrapper.h"
#include "states/playstate/goals/Goal_MoveToPosition.h"
#include "states/playstate/goals/Goal_SeekToPosition.h"
#include "states/playstate/goals/Goal_TraverseEdge.h"

#include "game/database/CActorType.h"

void RegisterToLuaTelegram( lua_State* Lua )
{
  module( Lua )[class_ < Telegram
      > ( "Telegram" ).def_readwrite( "Msg",
                                      &Telegram::Msg ).def_readwrite( "ExtraInfo",
                                                                      &Telegram::ExtraInfo )];
}
void RegisterToLuaMessageDispacher( lua_State* Lua )
{
  module( Lua )[class_ < MessageDispatcher
      > ( "Dispatch" ).def( "DispatchMsg",
                            &MessageDispatcher::DispatchMsg )];
  globals( Lua )["Dispatch"] = Dispatch; // Es una class singleton
}
void RegisterToLuaCrudeTimer( lua_State* Lua )
{
  module( Lua )[class_ < CrudeTimer
      > ( "Clock" ).def( "GetCurrentTime",
                         &CrudeTimer::GetCurrentTime )];
  globals( Lua )["Clock"] = Clock; // Es una class singleton
}
void RegisterToLuaVector2D( lua_State* Lua )
{
  module( Lua )[class_ < Vector2D
      > ( "Vector2D" ).def( constructor < >() ).def( constructor < double,
          double >() ).def( "Zero",
                            &Vector2D::Zero ).def_readwrite( "x",
                                                             &Vector2D::x ).def_readwrite( "y",
                                                                                           &Vector2D::y )];
}
void RegisterToLuaBaseGameEntity( lua_State* Lua )
{
  module( Lua )[class_ < BaseGameEntity
      > ( "BaseGameEntity" ).def( "ID",
                                  &BaseGameEntity::ID ).property( "m_vPos",
                                                                  &BaseGameEntity::Pos,
                                                                  &BaseGameEntity::SetPos ).property( "m_EntityType",
                                                                                                      &BaseGameEntity::EntityType,
                                                                                                      &BaseGameEntity::SetEntityType )];
}
void RegisterToLuaMovingEntity( lua_State* Lua )
{
  module( Lua )[class_ < MovingEntity, bases < BaseGameEntity >
      > ( "MovingEntity" )
  /*
   .property("m_vVelocity",&MovingEntity::Velocity,&MovingEntity::SetVelocity)
   */
  ];
}

void RegisterToLuaModel( lua_State* Lua )
{
  module( Lua )[class_ < Model > ( "Model" )];
}

void RegisterToLuaGameWorld( lua_State* Lua )
{
  module( Lua )[class_ < PlayModel, bases < Model > > ( "PlayModel" )
//		 .def("cxClient",&GameWorld::cxClient)
  ];
}

void RegisterToLuaGoal( lua_State* Lua )
{

  module( Lua )[class_ < Goal < CActorMapa >
      > ( "Goal" ).property( "m_pOwner",
                             &Goal < CActorMapa >::GetOwner )];

  module( Lua )[class_ < Goal_Composite < CActorMapa >, bases <
      Goal < CActorMapa > >
      > ( "Goal_Composite" ).def( "RemoveAllSubgoals",
                                  &Goal_Composite < CActorMapa >::RemoveAllSubgoals ).def( "AddSubgoal",
                                                                                           &Goal_Think::AddSubgoal,
                                                                                           adopt( _2 ) ) // Con esto dejamos que C++ maneje el destructor del
  // puntero a la clase pasado ??... !! Parece que funciona??.

  ];

  module( Lua )[class_ < Goal_Think, bases < Goal_Composite < CActorMapa > >, Goal_Think_wrapper
      > ( "Goal_Think" ).def( constructor < CActorMapa* >() ).def( "Arbitrate",
                                                                   &Goal_Think::Arbitrate,
                                                                   &Goal_Think_wrapper::default_Arbitrate )

  ];

  module( Lua )[class_ < Goal_Wander, bases < Goal < CActorMapa > >, Goal_Wander_wrapper
      > ( "Goal_Wander" ).def( constructor < CActorMapa* >() )];
  module( Lua )[class_ < Goal_MoveToPosition, bases <
      Goal_Composite < CActorMapa > >
      > ( "Goal_MoveToPosition" ).def( constructor < CActorMapa*, Vector2D >() )];
  /*
   module(Lua)
   [
   class_<Goal_SeekToPosition, bases <Goal<CActorMapa> > >("Goal_SeekToPosition")
   .def(constructor<CActorMapa*, Vector2D>())
   ];
   module(Lua)
   [
   class_<Goal_TraverseEdge, bases <Goal<CActorMapa> > >("Goal_TraverseEdge")
   .def(constructor<CActorMapa*, PathEdge, bool>())
   ];
   */
}
void RegisterToLuaActorMapa( lua_State* Lua )
{
  module( Lua )[class_ < CActorMapa, bases < MovingEntity >, ActorMapa_wrapper
      > ( "CActorMapa" ).enum_( "message_type" )[value( "Msg_PathReady",
                                                        CActorMapa::Msg_PathReady ), value( "Msg_NoPathAvailable",
                                                                                            CActorMapa::Msg_NoPathAvailable ), value( "Msg_Goto",
                                                                                                                                      CActorMapa::Msg_Goto )].def( constructor <
          PlayModel*, Vector2D, CActorType* >() ).def( "World",
                                                       &CActorMapa::World ).def( "HandleMessage",
                                                                                 &CActorMapa::HandleMessage,
                                                                                 &ActorMapa_wrapper::default_HandleMessage ).def( "UpdateFrame",
                                                                                                                                  &CActorMapa::UpdateFrame,
                                                                                                                                  &ActorMapa_wrapper::default_UpdateFrame ).property( "m_pBrain",
                                                                                                                                                                                      &CActorMapa::GetBrain,
                                                                                                                                                                                      &CActorMapa::SetBrain,
                                                                                                                                                                                      luabind::detail::null_type(),
                                                                                                                                                                                      adopt( _2 ) ).def( "SmoothingOn",
                                                                                                                                                                                                         &CActorMapa::SmoothingOn ).def( "isHeadingAt",
                                                                                                                                                                                                                                         &CActorMapa::isHeadingAt ).property( "m_Personality",
                                                                                                                                                                                                                                                                              &CActorMapa::GetPersonality,
                                                                                                                                                                                                                                                                              &CActorMapa::SetPersonality ).property( "m_State",
                                                                                                                                                                                                                                                                                                                      &CActorMapa::GetState,
                                                                                                                                                                                                                                                                                                                      &CActorMapa::SetState ).property( "m_Dir",
                                                                                                                                                                                                                                                                                                                                                        &CActorMapa::GetDir,
                                                                                                                                                                                                                                                                                                                                                        &CActorMapa::SetDir ).property( "m_iFrame",
                                                                                                                                                                                                                                                                                                                                                                                        &CActorMapa::GetFrame,
                                                                                                                                                                                                                                                                                                                                                                                        &CActorMapa::SetFrame ).property( "m_pSteering",
                                                                                                                                                                                                                                                                                                                                                                                                                          &CActorMapa::Steering )
//		 .def("isAtPosition",&CActorMapa::isAtPosition)
//		 .def("GetFSM",&CActorMapa::GetFSM)
//		 .def("GetPathPlanner",&CActorMapa::GetPathPlanner)
//		 .def("TengoPath",&CActorMapa::TengoPath)
//		 .property("m_iTimeElapsed", &CActorMapa::GetTimeElapsed, &CActorMapa::SetTimeElapsed)
//		 .property("m_LastTimeElapsed",&CActorMapa::GetLastTimeElapsed,&CActorMapa::SetLastTimeElapsed)

  ];
}
void RegisterToLuaCActorType( lua_State* Lua )
{
  module( Lua )[class_ < CActorType > ( "CActorType" )];
}
void RegisterToLuaSteeringBehavior( lua_State* Lua )
{
  module( Lua )[class_ < SteeringBehavior
      > ( "SteeringBehavior" ).def( "SeekOn",
                                    &SteeringBehavior::SeekOn ).def( "SeekOff",
                                                                     &SteeringBehavior::SeekOff ).def( "ArriveOn",
                                                                                                       &SteeringBehavior::ArriveOn ).def( "ArriveOff",
                                                                                                                                          &SteeringBehavior::ArriveOff ).def( "SeparationOn",
                                                                                                                                                                              &SteeringBehavior::SeparationOn ).def( "SeparationOff",
                                                                                                                                                                                                                     &SteeringBehavior::SeparationOff ).def( "WallAvoidanceOn",
                                                                                                                                                                                                                                                             &SteeringBehavior::WallAvoidanceOn ).property( "m_vTarget",
                                                                                                                                                                                                                                                                                                            &SteeringBehavior::Target,
                                                                                                                                                                                                                                                                                                            &SteeringBehavior::SetTarget )];
}
void RegisterToLuaCActor_PathPlanner( lua_State* Lua )
{
  module( Lua )[class_ < CActor_PathPlanner
      > ( "CActor_PathPlanner" ).def( "RequestPathToPosition",
                                      &CActor_PathPlanner::RequestPathToPosition )];
}
