/*
 * ModifierGoalActor.h
 *
 *  Created on: 15-ene-2009
 *      Author: 79481180
 */

#ifndef MODIFIERGOALACTOR_H_
#define MODIFIERGOALACTOR_H_

#include <list>

#include "navigation/ModifierGoalBase.h"

#include "game/BaseGameEntity.h"

#include "cactormapa.h"
#include "cellmapapartition.h"
#include "steeringbehaviors.h"

class ModifierGoalActor: public ModifierGoalBase
{

  public:

    ModifierGoalActor( CellMapaPartition < BaseGameEntity* >* cellmapa );
    virtual ~ModifierGoalActor();

    virtual bool NodeIsOpen( int node );

  private:

    CellMapaPartition < BaseGameEntity* >* m_pCellMapa;

};

#endif /* MODIFIERGOALACTOR_H_ */
