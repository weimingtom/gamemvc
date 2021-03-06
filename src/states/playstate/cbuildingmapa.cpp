/*
 * CBuildingMapa.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "cbuildingmapa.h"

#include <tinyxml.h>
#include <guichan.hpp>

#include <game/GameException.h>

#include <game/BaseGameEntity.h>
#include <game/database/CTile.h>

#include <game/database/CBuildingManager.h>
#include <game/database/CBuildingType.h>

#include "cbuildingmapamanager.h"
#include "playmodel.h"

CBuildingMapa::CBuildingMapa( PlayModel* model ) :
    BaseGameEntity( BaseGameEntity::building ), m_pModel( model )
{

}

bool CBuildingMapa::Load( TiXmlElement* pXMLData )
{

  if ( !pXMLData ) return false;
  gcn::Point p;
  THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute("x"),
                           "Error x BuildingMapa no definido" )
  p.x = atoi( pXMLData->Attribute( "x" ) );

  THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute("y"),
                           "Error y BuildingMapa no definido" )
  p.y = atoi( pXMLData->Attribute( "y" ) );

  std::string s( pXMLData->GetText() );
  m_pBuildingType = BuildingManager.GetBuildingType( s );

  m_pModel->FreeMapNodes( m_pBuildingType->GetSpace(),
                          p );

  SetPos( m_pModel->Map().MapToLocal < Vector2D >( gcn::Point( p.x,
                                                               p.y ) ) );
  m_pModel->GetCellMapa()->AddEntity( this );
  return true;
}
void CBuildingMapa::Draw( gcn::Graphics* graphics,
                          int destX,
                          int destY ) const
{

  m_pBuildingType->Draw( graphics,
                         destX,
                         destY );

}
