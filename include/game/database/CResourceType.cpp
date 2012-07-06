/*
 * CResourceType.cpp
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#include "CResourceType.h"

#include <tinyxml.h>
#include <guichan.hpp>

#include <game/GameException.h>

CResourceType::~CResourceType()
{

  delete m_pImage;

}
bool CResourceType::Load( TiXmlElement* pXMLData )
{

  if ( !pXMLData ) return false;

  THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute("name"),
                           "Error m_Name ResourceType no definido" );
  m_Name = pXMLData->Attribute( "name" );

  if ( pXMLData->Attribute( "AnchorX" ) ) {
    m_iAnchorX = atoi( pXMLData->Attribute( "AnchorX" ) );
  } else
    m_iAnchorX = 32;

  if ( pXMLData->Attribute( "AnchorY" ) ) {
    m_iAnchorY = atoi( pXMLData->Attribute( "AnchorY" ) );
  } else
    m_iAnchorY = 16;

  if ( pXMLData->Attribute( "space" ) ) {
    m_space = atoi( pXMLData->Attribute( "space" ) );
  } else
    m_space = 1;
  m_adjust = gcn::Point( 0,
                         0 );
  switch ( m_space )
  {

    case 4:
      // Centro de los 4 tiles.
//!TODO			m_adjust.X() = -mouse->w() / 2;
      m_adjust.x = -32;

      break;

    case 6:
      //Centro de los 6 tiles.
      // No hay desplazamiento.
      break;

    default:
      break;

  }THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute( "image" ),
                            "Error image ResourceType no definido" );
  std::string s( pXMLData->Attribute( "image" ) );
  m_pImage = gcn::Image::load( s );

  return true;
}

void CResourceType::Draw( gcn::Graphics* graphics,
                          int destX,
                          int destY ) const
{

  graphics->drawImage( m_pImage,
                       destX - m_iAnchorX + m_adjust.x,
                       destY - m_iAnchorY + m_adjust.y );

}

int CResourceType::GetSpace() const
{

  return m_space;

}

