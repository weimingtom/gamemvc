/*
 * ModifierGoalActor.cpp
 *
 *  Created on: 15-ene-2009
 *      Author: 79481180
 */
#include "modifiergoalactor.h"

ModifierGoalActor::ModifierGoalActor( CellMapaPartition < BaseGameEntity* >* cellmapa ) :
    m_pCellMapa( cellmapa )
{

}

ModifierGoalActor::~ModifierGoalActor()
{

}

bool ModifierGoalActor::NodeIsOpen( int node )
{

  bool res = true;
  std::list < BaseGameEntity* > members = m_pCellMapa->GetCell( node ).Members;

  std::list < BaseGameEntity* >::iterator iter;
  for ( iter = members.begin(); ( iter != members.end() ) && res; iter++ ) {

    if ( BaseGameEntity::actor == ( *iter )->EntityType() ) {

      if ( !static_cast < CActorMapa* >( *iter )->Steering()->SeparationIsOn() ) {
        res = false;
      }

    }
  }
  return res;
}
