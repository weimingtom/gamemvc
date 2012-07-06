/*
 * CResourceMapa.cpp
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#include "cresourcemapa.h"

#include <tinyxml.h>
#include <guichan.hpp>

#include <game/GameException.h>

#include <game/BaseGameEntity.h>
#include <game/database/CResourceManager.h>
#include <game/database/CResourceType.h>

#include "cresourcemapamanager.h"
#include "playmodel.h"

CResourceMapa::CResourceMapa( PlayModel* model ) :
    BaseGameEntity( BaseGameEntity::resource ), m_pModel( model )
{

}

bool CResourceMapa::Load( TiXmlElement* pXMLData )
{

  if ( !pXMLData ) return false;
  gcn::Point p;
  THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute("x"),
                           "Error x ResourceMapa no definido" )
  p.x = atoi( pXMLData->Attribute( "x" ) );

  THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute("y"),
                           "Error y ResourceMapa no definido" )
  p.y = atoi( pXMLData->Attribute( "y" ) );

  std::string s( pXMLData->GetText() );
  m_pResourceType = ResourceManager.GetResourceType( s );

  m_pModel->FreeMapNodes( m_pResourceType->GetSpace(),
                          p );

  SetPos( m_pModel->Map().MapToLocal < Vector2D >( gcn::Point( p.x,
                                                               p.y ) ) );
  m_pModel->GetCellMapa()->AddEntity( this );
  return true;
}
void CResourceMapa::Draw( gcn::Graphics* graphics,
                          int destX,
                          int destY ) const
{

  m_pResourceType->Draw( graphics,
                         destX,
                         destY );

}

