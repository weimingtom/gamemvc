/*
 * CResourceMapaManager.cpp
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#include "cresourcemapamanager.h"

#include <tinyxml.h>

#include "playmodel.h"
#include "cresourcemapa.h"

CResourceMapaManager::CResourceMapaManager( PlayModel* model ) :
    m_pModel( model )
{

}

bool CResourceMapaManager::Load( TiXmlElement* pXMLData )
{

  if ( !pXMLData ) return false;

  TiXmlElement *pResourceMapa = NULL;
  pResourceMapa = pXMLData->FirstChildElement( "resource" );
  // Loop through each type in the Actor

  while ( pResourceMapa ) {

    CResourceMapa_ptr elResourceMapa( new CResourceMapa( m_pModel ) );

    if ( elResourceMapa->Load( pResourceMapa ) == false ) return false;

    m_ResourceMapa.push_back( elResourceMapa );
    pResourceMapa = pResourceMapa->NextSiblingElement( "resource" );

  }

  return true;

}

