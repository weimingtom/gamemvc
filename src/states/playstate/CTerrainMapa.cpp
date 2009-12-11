/*
 * CTerrainMapa.cpp
 *
 *  Created on: 29-dic-2008
 *      Author: Administrador
 */

#include "CTerrainMapa.h"

#include <game/BaseGameEntity.h>
#include <game/database/CTile.h>
#include <guichan.hpp>

#include "PlayModel.h"

CTerrainMapa::CTerrainMapa( PlayModel* model ) :
	BaseGameEntity( BaseGameEntity::terrain ), m_pModel( model ) {

}

CTerrainMapa::~CTerrainMapa() {

}
void CTerrainMapa::SetTile( CTile* tile,
							const gcn::Point& p ) {
	m_pTerrain = tile;

	SetPos( m_pModel->getMap().MapToLocal( 	p.GetX(),
											p.GetY() ) );
	m_pModel->GetCellPartition()->AddEntity( this );

}
void CTerrainMapa::Draw( 	gcn::Graphics* graphics,
							int destX,
							int destY ) {

	m_pTerrain->Draw( 	graphics,
						destX,
						destY );

}
