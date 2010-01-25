/*
 * PlayModel.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "PlayModel.h"

#include <tinyxml.h>

#include <misc/Interface.h>
#include <misc/debug.h>
#include <2d/WallIntersectionTests.h>
#include <Graph/HandyGraphFunctions.h>
#include <Messaging/MessageDispatcher.h>
#include <game/GameException.h>
#include <Lua/CLuaManager.h>

#include <MyGame.h>

#include "lua/Raven_Scriptor.h"

#include "CActor_PathPlanner.h"
#include "CTerrainMapa.h"
#include "CBuildingMapa.h"
#include "CResourceMapa.h"

const int SIZELOCAL = 64; // Tamaño en puntos de cada cuadrado local....
//--------------------------- GraphHelper_CreateGrid --------------------------
//
//  creates a graph based on a grid layout. This function requires the
//  dimensions of the environment and the number of cells required horizontally
//  and vertically
//-----------------------------------------------------------------------------
template < class graph_type >
void GraphHelper_CreateGridOwn( graph_type& graph,
								int cySize,
								int cxSize,
								int NumCellsY,
								int NumCellsX ) {
	//need some temporaries to help calculate each node center
	double CellWidth = (double) cySize / (double) NumCellsX;
	double CellHeight = (double) cxSize / (double) NumCellsY;

	double midX = CellWidth / 2;
	double midY = CellHeight / 2;

	//first create all the nodes
	for ( int row = 0; row < NumCellsY; ++row ) {
		for ( int col = 0; col < NumCellsX; ++col ) {

			graph.AddNode( NavGraphNode < Trigger < CActorMapa >* > ( 	graph.GetNextFreeNodeIndex(),
																		Vector2D( 	midX
																							+ ( col
																									* CellWidth ),
																					midY
																							+ ( row
																									* CellHeight ) ) ) );

		}
	}
	//now to calculate the edges. (A position in a 2d array [x][y] is the
	//same as [y*NumCellsX + x] in a 1d array). Each cell has up to eight
	//neighbours.
	for ( int row = 0; row < NumCellsY; ++row ) {
		for ( int col = 0; col < NumCellsX; ++col ) {
			GraphHelper_AddAllNeighboursToGridNode( graph,
													row,
													col,
													NumCellsX,
													NumCellsY );
		}
	}
}

PlayModel::PlayModel(MyGame& game) :
	Model(),
	m_game_(game),
	m_endtype( PlayModel::CONTINUE ), m_maplocal( SIZELOCAL ),
			m_ismouse( false ), m_pMapaPartition( NULL ),
			m_pSpacePartition( NULL ), m_pNavGraph( NULL ),
			m_pPathManager( NULL ) {

	//
	//	Cargar los datos de este juego.
	//
	loadGame( "./scripts/xml/mapa.xml" );

}

PlayModel::~PlayModel() {

	delete m_pMapaPartition;
	delete m_pNavGraph;
	delete m_pSpacePartition;

	delete m_pActorMapaManager;
	delete m_pBuildingMapaManager;
	delete m_pResourceMapaManager;
	delete m_pTerrainMapaManager;

	delete m_pPathManager;

	DeleteSTLContainer( m_Walls );

	LuaManager.RunLuaDoString( "collectgarbage (\"collect\")" ); // Recojemos Lua para no dejar memoria suelta.

}
void PlayModel::Update(long iElapsedTicks) {

	//update all the queued searches in the path manager
	m_pPathManager->UpdateSearches();
	/*
	 * De momento solo actualizamos los Actores y a lo bruto
	 * veremos a ver como lo mejoro.
	 */
	std::vector < CActorMapa_ptr >::iterator iter;
	std::vector < CActorMapa_ptr >& actorsMapa = m_pActorMapaManager->_getActors();
	for ( iter = actorsMapa.begin(); iter != actorsMapa.end(); ++iter ) {
		( *iter )->Update( iElapsedTicks );
	}
	Dispatch->DispatchDelayedMessages();

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
void PlayModel::setMouse(	const std::string& name,
							const int& X,
							const int& Y ) {
	m_ismouse = true;
	m_MsgLeftname = name;
	m_MsgLeftX = X;
	m_MsgLeftY = Y;
}
void PlayModel::resetMouse() {
	m_ismouse = false;
}
bool PlayModel::ismouse() const {
	return m_ismouse;
}
const std::string& PlayModel::getMsgLeftname() const {
	return m_MsgLeftname;
}
int PlayModel::getMsgLeftX() const {
	return m_MsgLeftX;
}
int PlayModel::getMsgLeftY() const {
	return m_MsgLeftY;
}
std::vector < CTerrainMapa* > PlayModel::ObtainTerrainCell( const gcn::Point& pLocal ) {

	std::vector < CTerrainMapa* > terrainCell;

	CellMapa < BaseGameEntity* > cell =
			GetCellMapa()->GetCell( Vector2D( 	pLocal.x,
												pLocal.y ) );

	std::list < BaseGameEntity* >::iterator iter;
	for ( iter = cell.Members.begin(); iter != cell.Members.end(); ++iter ) {

		if ( ( *iter )->EntityType() == BaseGameEntity::terrain ) {

			CTerrainMapa* terrain = static_cast < CTerrainMapa* > ( *iter );
			terrainCell.push_back( terrain );

		}
	}
	return terrainCell;
}
std::vector < CBuildingMapa* > PlayModel::ObtainBuildingCell( const gcn::Point& pLocal ) {

	std::vector < CBuildingMapa* > buildingCell;

	CellMapa < BaseGameEntity* > cell =
			GetCellMapa()->GetCell( Vector2D( 	pLocal.x,
												pLocal.y ) );

	std::list < BaseGameEntity* >::iterator iter;
	for ( iter = cell.Members.begin(); iter != cell.Members.end(); ++iter ) {

		if ( ( *iter )->EntityType() == BaseGameEntity::building ) {

			CBuildingMapa* terrain = static_cast < CBuildingMapa* > ( *iter );
			buildingCell.push_back( terrain );

		}
	}

	return buildingCell;
}
std::vector < CResourceMapa* > PlayModel::ObtainResourceCell( const gcn::Point& pLocal ) {

	std::vector < CResourceMapa* > ResourceCell;

	CellMapa < BaseGameEntity* > cell =
			GetCellMapa()->GetCell( Vector2D( 	pLocal.x,
												pLocal.y ) );

	std::list < BaseGameEntity* >::iterator iter;
	for ( iter = cell.Members.begin(); iter != cell.Members.end(); ++iter ) {

		if ( ( *iter )->EntityType() == BaseGameEntity::resource ) {

			CResourceMapa* terrain = static_cast < CResourceMapa* > ( *iter );
			ResourceCell.push_back( terrain );

		}
	}

	return ResourceCell;
}
std::vector < CActorMapa* > PlayModel::ObtainActorCell( const gcn::Point& pLocal ) {

	std::vector < CActorMapa* > ActorCell;

	CellMapa < BaseGameEntity* > cell =
			GetCellMapa()->GetCell( Vector2D( 	pLocal.x,
												pLocal.y ) );

	std::list < BaseGameEntity* >::iterator iter;
	for ( iter = cell.Members.begin(); iter != cell.Members.end(); ++iter ) {

		if ( ( *iter )->EntityType() == BaseGameEntity::actor ) {

			CActorMapa* terrain = static_cast < CActorMapa* > ( *iter );
			ActorCell.push_back( terrain );

		}
	}

	return ActorCell;
}
int PlayModel::getResolution() const {

	return m_iResolution;

}
int PlayModel::getTopPadding() const {

	return m_iTopPadding;

}
const std::string& PlayModel::getMouseMap() const {
	return m_sMouseMap;
}
const MapLocal& PlayModel::Map() const {
	return m_maplocal;
}
int PlayModel::cxClient() const{
	return m_iSizeX;
}
int PlayModel::cyClient() const{
	return m_iSizeY;
}
const Interface& PlayModel::interface() const{
	return m_game_.interface();
}
//------------------------- isPathObstructed ----------------------------------
//
//  returns true if a bot cannot move from A to B without bumping into
//  world geometry. It achieves this by stepping from A to B in steps of
//  size BoundingRadius and testing for intersection with world geometry at
//  each point.
//-----------------------------------------------------------------------------
bool PlayModel::isPathObstructed( 	Vector2D A,
									Vector2D B,
									double BoundingRadius ) const {
	Vector2D ToB = Vec2DNormalize( B - A );

	Vector2D curPos = A;

	while ( Vec2DDistanceSq( 	curPos,
								B ) > BoundingRadius * BoundingRadius ) {
		//advance curPos one step
		curPos += ToB * 0.5 * BoundingRadius;

		//test all walls against the new position
		if ( doWallsIntersectCircle( 	GetWalls(),
										curPos,
										BoundingRadius ) ) {
			return true;
		}

	}

	return false;
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
	//
	// Ya tenemos los datos de cabecera del juego,
	// procedemos crear el mapa donde
	// los vamos a representar.
	//

	//
	// Aqui creo que es un buen momento para definir lo relativo a
	// path finder, tenemos el terreno base y su tamao.
	//
	m_iSizeX = m_iResolution * SIZELOCAL; //!TODO Esto esta mal ojo....
	m_iSizeY = m_iResolution * SIZELOCAL; //

	m_iCellsX = m_iResolution;
	m_iCellsY = m_iResolution;

	m_pMapaPartition = new CellMapaPartition < BaseGameEntity* > ( 	m_iSizeX,
																	m_iSizeY,
																	m_iCellsX,
																	m_iCellsY );
	//delete any old graph
	delete m_pNavGraph;

	//create the graph
	m_pNavGraph = new NavGraph( false );//not a digraph
	GraphHelper_CreateGridOwn(	*m_pNavGraph,
								m_iSizeX,
								m_iSizeY,
								m_iCellsX,
								m_iCellsY );

	/*
	 * Cargar los datos de los objetos del juego, que modifican
	 * el posible calculo del pathfinder.
	 *
	 * 	1.- El terreno ( en funcion del tipo se modifica el path finder ).
	 *  2.- Los recursos ( arboles , minas, etc... ).
	 *  3.- Los Buildings.
	 *  4.- Los Actores.
	 *
	 */
	THROW_GAME_EXCEPTION_IF(!loadTerrain( pXMLData ),"Error loadTerrain");
	THROW_GAME_EXCEPTION_IF(!loadResource( pXMLData ),"Error loadResource");
	THROW_GAME_EXCEPTION_IF(!loadBuilding( pXMLData ), "Error loadBuilding");

	//partition the graph nodes
	PartitionNavGraph();

	m_pPathManager
			= new
					PathManager < CActor_PathPlanner > ( script->GetDouble( "MaxSearchCyclesPerUpdateStep" ) );

	THROW_GAME_EXCEPTION_IF(!loadActor( pXMLData ), "Error loadBuilding");
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

	THROW_GAME_EXCEPTION_IF(!pXMLData->Attribute("mouse"),"Mouse map no definido");
	m_sMouseMap = pXMLData->Attribute( "mouse" );

	return true;

}

//-------------------------------------------------------------------
bool PlayModel::loadTerrain( TiXmlElement* pXMLData ) {

	//
	// Procesamos el terreno.
	//
	m_pTerrainMapaManager = new CTerrainMapaManager( this );
	return m_pTerrainMapaManager->Load( pXMLData->FirstChildElement( "TerrainGroup" ) );

}
bool PlayModel::loadBuilding( TiXmlElement* pXMLData ) {
	//
	// Cargamos datos iniciales de Buildings.
	//
	m_pBuildingMapaManager = new CBuildingMapaManager( this );
	return m_pBuildingMapaManager->Load( pXMLData->FirstChildElement( "BuildingGroup" ) );

}
bool PlayModel::loadResource( TiXmlElement* pXMLData ) {
	//
	// Cargamos datos iniciales de Resources.
	//
	m_pResourceMapaManager = new CResourceMapaManager( this );
	return m_pResourceMapaManager->Load( pXMLData->FirstChildElement( "ResourceGroup" ) );

}
bool PlayModel::loadActor( TiXmlElement* pXMLData ) {
	//
	// Cargamos datos iniciales de Resources.
	//
	m_pActorMapaManager = new CActorMapaManager( this );
	if (!m_pActorMapaManager->Load( pXMLData->FirstChildElement( "ActorGroup" ) )) return false;

	std::vector < CActorMapa_ptr >::iterator iter;
	std::vector < CActorMapa_ptr>& actorMapa = m_pActorMapaManager->_getActors();
	for ( iter = actorMapa.begin(); iter != actorMapa.end(); iter++ )
		m_Vehicles.push_back( ( *iter ).get() );
	return true;

}

//-------------------------- PartitionEnvironment -----------------------------
//-----------------------------------------------------------------------------
void PlayModel::PartitionNavGraph() {

	if ( m_pSpacePartition )
		delete m_pSpacePartition;

	m_pSpacePartition
			= new CellSpacePartition < NavGraph::NodeType* > ( 	m_iSizeX,
																m_iSizeY,
																m_iCellsX,
																m_iCellsY,
																m_pNavGraph->NumNodes() );

	//add the graph nodes to the space partition
	NavGraph::NodeIterator NodeItr( *m_pNavGraph );
	for ( NavGraph::NodeType* pN = NodeItr.begin(); !NodeItr.end(); pN
			= NodeItr.next() ) {
		m_pSpacePartition->AddEntity( pN );
	}
}

