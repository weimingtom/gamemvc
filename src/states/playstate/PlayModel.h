/*
 * PlayModel.h
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#ifndef PLAYMODEL_H_
#define PLAYMODEL_H_

#include <memory>
#include <string>

#include <2d/Vector2D.h>
#include <mvc/Model.h>
#include <misc/Point.h>
#include <misc/CellSpacePartition.h>
#include <game/IsoDiamondMap.h>
#include <game/EntityFunctionTemplates.h>

#include <Graph/GraphEdgeTypes.h>
#include <Graph/GraphNodeTypes.h>
#include <Graph/SparseGraph.h>

#include "Triggers/Trigger.h"
#include "Triggers/TriggerSystem.h"

#include "navigation/PathManager.h"

#include "CellMapaPartition.h"
#include "CTerrainMapaManager.h"
#include "CBuildingMapaManager.h"
#include "CResourceMapaManager.h"
#include "CActorMapaManager.h"

class TiXmlElement;
class CActor_PathPlanner;
class CActorMapa;
class Wall2D;

class PlayModel: public Model
{
public:

	enum EndTypes
	{
		CONTINUE = -1,
		QUIT,
		MENU

	};

	typedef CellMapaPartition < BaseGameEntity* > CellPartition;

	typedef NavGraphNode < Trigger < CActorMapa >* > GraphNode;
	typedef SparseGraph < GraphNode, NavGraphEdge > NavGraph;
	typedef CellSpacePartition < NavGraph::NodeType* > CellSpace;

	typedef Trigger < CActorMapa > TriggerType;
	typedef TriggerSystem < TriggerType > TheTriggerSystem;

	PlayModel();
	virtual ~PlayModel();

	bool isEnd();
	void setEnd( const PlayModel::EndTypes& type );
	PlayModel::EndTypes getEnd() const;

	int getResolution();
	int getTopPadding();

	void Update();

	std::vector < CTerrainMapa* > ObtainTerrainCell( const gcn::Point& pLocal );
	std::vector < CBuildingMapa* >
	ObtainBuildingCell( const gcn::Point& pLocal );
	std::vector < CResourceMapa* >
	ObtainResourceCell( const gcn::Point& pLocal );
	std::vector < CActorMapa* > ObtainActorCell( const gcn::Point& pLocal );

	IsoDiamondMap& getMap() const;

	NavGraph& GetNavGraph() const {
		return *m_pNavGraph;
	}
	PathManager < CActor_PathPlanner >* const GetPathManager() {
		return m_pPathManager;
	}

	CellSpace* const GetCellSpace() const {
		return m_pSpacePartition;
	}
	CellPartition* const GetCellMapa() const {
		return m_pMapaPartition.get();
	}
	const std::vector < Wall2D* >& GetWalls() const {
		return m_Walls;
	}
	const std::vector < CActorMapa* >& GetAllBots() {
		return m_Vehicles;
	}
	void TagVehiclesWithinViewRange( 	BaseGameEntity* pVehicle,
										double range ) {
		TagNeighbors( 	pVehicle,
						m_Vehicles,
						range );
	}
	bool isPathObstructed( 	Vector2D A,
							Vector2D B,
							double BoundingRadius ) const;
private:

	PlayModel::EndTypes m_endtype;

	std::string m_sMapName;
	int m_iResolution;
	int m_iTopPadding;

	int m_iSizeX;
	int m_iSizeY;

	int m_iCellsX;
	int m_iCellsY;

	std::auto_ptr < CellPartition > m_pMapaPartition; //! Division del mapa isometrico?.

	//the graph nodes will be partitioned enabling fast lookup
	CellSpace* m_pSpacePartition;

	std::auto_ptr < IsoDiamondMap > m_map;

	NavGraph* m_pNavGraph; //! This Map navigation graph.

	//this class manages all the path planning requests
	PathManager < CActor_PathPlanner >* m_pPathManager;

	//the walls that comprise the current map's architecture.
	std::vector < Wall2D* > m_Walls;

	//a container of all the moving entities
	std::vector < CActorMapa* > m_Vehicles;

	typedef std::auto_ptr < CTerrainMapaManager > CTerrainMapaManager_ptr;
	typedef std::auto_ptr < CBuildingMapaManager > CBuildingMapaManager_ptr;
	typedef std::auto_ptr < CResourceMapaManager > CResourceMapaManager_ptr;
	typedef std::auto_ptr < CActorMapaManager > CActorMapaManager_ptr;

	CTerrainMapaManager_ptr m_pTerrainMapaManager;
	CBuildingMapaManager_ptr m_pBuildingMapaManager;
	CResourceMapaManager_ptr m_pResourceMapaManager;
	CActorMapaManager_ptr m_pActorMapaManager;

	void loadGame( const std::string& mapData );
	bool loadXML( TiXmlElement* pXMLData );
	//
	bool loadTerrain( TiXmlElement* pXMLData );
	bool loadBuilding( TiXmlElement* pXMLData );
	bool loadResource( TiXmlElement* pXMLData );
	bool loadActor( TiXmlElement* pXMLData );

};

#endif /* PLAYMODEL_H_ */
