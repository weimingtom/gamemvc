/*
 * CTerrainMapaManager.cpp
 *
 *  Created on: 29-dic-2008
 *      Author: Administrador
 */

#include "cterrainmapamanager.h"

#include <tinyxml.h>
#include <game/GameException.h>

#include <game/database/CTerrainManager.h>
#include <game/database/CTerrainType.h>

#include <misc/utils.h>

#include "playmodel.h"

#include "cterrainmapa.h"

CTerrainMapaManager::CTerrainMapaManager( PlayModel* model ) :
    m_pModel( model )
{

}

bool CTerrainMapaManager::Load( TiXmlElement* pXMLData )
{

  if ( !pXMLData ) return false;

  THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute( "default" ),
                           "Error Mapa: terreno por defecto no definido" );
  std::string sTerrain( pXMLData->Attribute( "default" ) );

  CTerrainType* pTerrain = TerrainManager.GetTerrainType( sTerrain );
  THROW_GAME_EXCEPTION_IF( !( pTerrain ),
                           "Error Mapa: el tipo de terreno " + sTerrain );

  int basex = 0;
  int basey = 0;
  int raiz = 3; //!TODO Realizar bien esto
  basey = 0;
  for ( int y = 0; y < m_pModel->getResolution(); y++ ) {

    basex = 0;
    for ( int x = 0; x < m_pModel->getResolution(); x++ ) {

      CTerrainMapa_ptr terrain( new CTerrainMapa( m_pModel ) );
      terrain->SetTile( pTerrain->GetTile( basex ),
                        gcn::Point( x,
                                    y ) );
      m_TerrainMapa.push_back( terrain );

      basex = ( ( basex + 1 ) % raiz ) + basey * raiz;

    }

    basey = ( basey + 1 ) % raiz;

  }

  return true;

}
