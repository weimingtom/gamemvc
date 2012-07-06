/*
 * CTerrainMapa.cpp
 *
 *  Created on: 29-dic-2008
 *      Author: Administrador
 */

#include "cterrainmapa.h"

#include <game/BaseGameEntity.h>
#include <game/database/CTile.h>
#include <guichan.hpp>

#include "playmodel.h"

CTerrainMapa::CTerrainMapa( PlayModel* model ) :
    BaseGameEntity( BaseGameEntity::terrain ), m_pModel( model )
{

}

CTerrainMapa::~CTerrainMapa()
{

}
void CTerrainMapa::SetTile( CTile* tile,
                            const gcn::Point& pMap )
{

  m_pTerrain = tile;
  SetPos( m_pModel->Map().MapToLocal < Vector2D >( pMap ) );

  m_pModel->GetCellMapa()->AddEntity( this );

}
void CTerrainMapa::Draw( gcn::Graphics* graphics,
                         int destX,
                         int destY ) const
{

  m_pTerrain->Draw( graphics,
                    destX,
                    destY );

}
