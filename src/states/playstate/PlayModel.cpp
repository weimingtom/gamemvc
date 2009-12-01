/*
 * PlayModel.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "PlayModel.h"

#include <tinyxml.h>

#include <misc/debug.h>

#include <game/GameException.h>
#include <game/database/CMouseMapManager.h>

#include "CTerrainMapa.h"
#include "CBuildingMapa.h"

PlayModel::PlayModel() :
	Model(),
	m_endtype( PlayModel::CONTINUE ),
	m_pCellPartition( NULL ) {

	//
	//	Cargar los datos de este juego.
	//
	loadGame( "./scripts/xml/mapa.xml" );

}

PlayModel::~PlayModel() {

}
void PlayModel::Update() {

}
bool PlayModel::isEnd() {

	return m_endtype != PlayModel::CONTINUE;

}
void PlayModel::setEnd( const PlayModel::EndTypes& type ) {

	m_endtype = type;
}
PlayModel::EndTypes PlayModel::getEnd() const {

	return m_endtype;

}
Vector2D PlayModel::IsoToLocal( Vector2D p ) {

	Vector2D local;
	local.x = p.x * mouse->w() + mouse->w() / 2;
	local.y = p.y * mouse->w() + mouse->w() / 2;

	return local;
}

CPoint PlayModel::IsoToLocal( CPoint p ) {

	CPoint local;
	local.X() = p.X() * mouse->w() + mouse->w() / 2;
	local.Y() = p.Y() * mouse->w() + mouse->w() / 2;

	return local;
}
Vector2D PlayModel::IsoToLocal( int ix,
								int iy ) {

	return IsoToLocal( Vector2D( 	ix,
									iy ) );

}
std::vector < CTerrainMapa* > PlayModel::ObtainTerrainCell( const CPoint& pLocal ) {

	std::vector < CTerrainMapa* > terrainCell;

	CellMapa < BaseGameEntity* > cell =
			GetCellPartition()->GetCell( Vector2D( 	pLocal.GetX(),
													pLocal.GetY() ) );

	std::list < BaseGameEntity* >::iterator iter;
	for ( iter = cell.Members.begin(); iter != cell.Members.end(); ++iter ) {

		if ( ( *iter )->EntityType() == BaseGameEntity::terrain ) {

			CTerrainMapa* terrain = static_cast < CTerrainMapa* > ( *iter );
			terrainCell.push_back( terrain );

		}
	}
	return terrainCell;
}
std::vector < CBuildingMapa* > PlayModel::ObtainBuildingCell( const CPoint& pLocal ) {

	std::vector < CBuildingMapa* > buildingCell;

	CellMapa < BaseGameEntity* > cell =
			GetCellPartition()->GetCell( Vector2D( 	pLocal.GetX(),
													pLocal.GetY() ) );

	std::list < BaseGameEntity* >::iterator iter;
	for ( iter = cell.Members.begin(); iter != cell.Members.end(); ++iter ) {

		if ( ( *iter )->EntityType() == BaseGameEntity::building ) {

			CBuildingMapa* terrain = static_cast < CBuildingMapa* > ( *iter );
			buildingCell.push_back( terrain );

		}
	}
	return buildingCell;
}
int PlayModel::getResolution() {

	return m_iResolution;

}
int PlayModel::getTopPadding() {

	return m_iTopPadding;

}
PlayModel::CellPartition* const PlayModel::GetCellPartition() const {

	return m_pCellPartition.get();

}
/*
 * ---------------------------------------------------------------------------------
 * Procedimientos privados
 * ---------------------------------------------------------------------------------
 */
void PlayModel::loadGame( const std::string& mapData ) {

	TiXmlDocument doc;
	TiXmlElement* pXMLData = NULL;

	THROW_GAME_EXCEPTION_IF( !doc.LoadFile( mapData.c_str() ),
			"XML error: " + mapData );

	pXMLData = doc.FirstChildElement( "map" );
	THROW_GAME_EXCEPTION_IF( !loadXML( pXMLData ),
			"Error no ChildElement <map> procesando : "
			+ mapData );
	/*
	 * Aqui creo que es un buen momento para definir lo relativo a
	 * path finder, tenemos el terreno base y su tamao.
	 */

	m_iSizeX = m_iResolution * mouse->w();
	m_iSizeY = m_iResolution * mouse->w();

	m_iCellsX = m_iResolution;
	m_iCellsY = m_iResolution;

	m_pCellPartition.reset( new
			CellMapaPartition < BaseGameEntity* > ( m_iSizeX,
													m_iSizeY,
													m_iCellsX,
													m_iCellsY ) );
	/*
	 * Cargar los datos de los objetos del juego, que modifican
	 * el posible calculo del pathfinder.
	 *
	 * 	1.- El terreno ( en funcion del tipo se modifica el path finder ).
	 *  2.- Los recursos ( arboles , minas, etc... ).
	 *  3.- Los Buildings.
	 *
	 */
	loadTerrain( pXMLData );
	//	loadResource( pXMLData );
	loadBuilding( pXMLData );

	return;
}
bool PlayModel::loadXML( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute( "name" ),
			"Error Mapa: nombre no definido" );
	m_sMapName = pXMLData->Attribute( "name" );

	THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute( "resolution" ),
			"Error Mapa: resolucion no definida" );
	m_iResolution = atoi( pXMLData->Attribute( "resolution" ) );

	THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute( "toppadding" ),
			"Error Mapa: Top Padding no definido" );
	m_iTopPadding = atoi( pXMLData->Attribute( "toppadding" ) );
	return true;

}

//-------------------------------------------------------------------
bool PlayModel::loadTerrain( TiXmlElement* pXMLData ) {

	/*
	 * Procesamos el terreno.
	 *
	 * Vemos si tenemos el terreno por defecto para crearlo como tal.
	 *
	 */
	m_pTerrainMapaManager.reset( new CTerrainMapaManager( this ) );
	if ( m_pTerrainMapaManager->Load( pXMLData->FirstChildElement( "TerrainGroup" ) )
			== false ) return false;

	return true;

}
bool PlayModel::loadBuilding( TiXmlElement* pXMLData ) {
	/*
	 * Cargamos datos iniciales de Buildings.
	 */
	m_pBuildingMapaManager.reset(new CBuildingMapaManager(this));

	if ( m_pBuildingMapaManager->Load( pXMLData->FirstChildElement( "BuildingGroup" ) )
			== false )
		return false;

	return true;
}
