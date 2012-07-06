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
#include <guichan.hpp>

#include <2d/Vector2D.h>
#include <mvc/Model.h>

#include <misc/CellSpacePartition.h>
#include <game/EntityFunctionTemplates.h>

#include <Graph/GraphEdgeTypes.h>
#include <Graph/GraphNodeTypes.h>
#include <Graph/SparseGraph.h>

#include "Triggers/Trigger.h"
#include "Triggers/TriggerSystem.h"

#include "navigation/PathManager.h"

#include "cellmapapartition.h"
#include "cterrainmapamanager.h"
#include "cbuildingmapamanager.h"
#include "cresourcemapamanager.h"
#include "cactormapamanager.h"
#include "maplocal.h"

class TiXmlElement;
class CActor_PathPlanner;
class CActorMapa;
class Wall2D;
class MyGame;
class Interface;

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

    PlayModel( MyGame& game );
    virtual ~PlayModel();

    bool isEnd();
    void setEnd( const PlayModel::EndTypes& type );
    PlayModel::EndTypes getEnd() const;

    int getResolution() const;
    int getTopPadding() const;
    const std::string& getNameMouseMap() const;

    MapLocal& Map();

    void Update( long iElapsedTicks );

    void setMouse( const std::string& name,
                   const int& X,
                   const int& Y );
    void resetMouse();
    const std::string& getMsgLeftname() const;
    int getMsgLeftX() const;
    int getMsgLeftY() const;
    bool ismouse() const;

    std::vector < CTerrainMapa* > ObtainTerrainCell( const gcn::Point& pLocal );
    std::vector < CBuildingMapa* >
    ObtainBuildingCell( const gcn::Point& pLocal );
    std::vector < CResourceMapa* >
    ObtainResourceCell( const gcn::Point& pLocal );
    std::vector < CActorMapa* > ObtainActorCell( const gcn::Point& pLocal );

    NavGraph& GetNavGraph() const
    {
      return *m_pNavGraph;
    }
    PathManager < CActor_PathPlanner >* const GetPathManager()
    {
      return m_pPathManager;
    }

    CellSpace* const GetCellSpace() const
    {
      return m_pSpacePartition;
    }
    CellPartition* const GetCellMapa() const
    {
      return m_pMapaPartition;
    }
    const std::vector < Wall2D* >& GetWalls() const
    {
      return m_Walls;
    }
    const std::vector < CActorMapa* >& GetAllBots()
    {
      return m_Vehicles;
    }
    void TagVehiclesWithinViewRange( BaseGameEntity* pVehicle,
                                     double range )
    {
      TagNeighbors( pVehicle,
                    m_Vehicles,
                    range );
    }
    bool isPathObstructed( Vector2D A,
                           Vector2D B,
                           double BoundingRadius ) const;
    int cxClient() const;
    int cyClient() const;
    const Interface& interface() const;
    int getSizeLocal() const;
    void FreeMapNodes( const int& num_nodes,
                       const gcn::Point base );
    bool RenderNeighbors() const
    {
      return m_bRenderNeighbors;
    }
    void moveToPosition( const gcn::Point& pos );
    void selectMultipleActors( const gcn::Point& point );
    void select1Actor( const gcn::Point& local );
    void clearMultipleActors();

  private:

    MyGame& m_game_;
    PlayModel::EndTypes m_endtype;

    std::string m_sMapName;
    int m_iResolution;
    int m_iTopPadding;
    std::string m_sMouseMap;
    MapLocal m_maplocal;

    int m_iSizeX;
    int m_iSizeY;

    int m_iCellsX;
    int m_iCellsY;

    // Datos para sacar en la view con el mouse.
    bool m_ismouse;
    std::string m_MsgLeftname;
    int m_MsgLeftX;
    int m_MsgLeftY;

    CellPartition* m_pMapaPartition; //! Division del mapa isometrico?.

    //the graph nodes will be partitioned enabling fast lookup
    CellSpace* m_pSpacePartition;

    NavGraph* m_pNavGraph; //! This Map navigation graph.

    //this class manages all the path planning requests
    PathManager < CActor_PathPlanner >* m_pPathManager;

    bool m_bRenderNeighbors;

    //the walls that comprise the current map's architecture.
    std::vector < Wall2D* > m_Walls;

    //a container of all the moving entities
    std::vector < CActorMapa* > m_Vehicles;

    // container todos los actores seleccionados.
    std::vector < CActorMapa* > m_ActorSelected;

    CTerrainMapaManager* m_pTerrainMapaManager;
    CBuildingMapaManager* m_pBuildingMapaManager;
    CResourceMapaManager* m_pResourceMapaManager;
    CActorMapaManager* m_pActorMapaManager;

    void loadGame( const std::string& mapData );
    bool loadXML( TiXmlElement* pXMLData );
    //
    bool loadTerrain( TiXmlElement* pXMLData );
    bool loadBuilding( TiXmlElement* pXMLData );
    bool loadResource( TiXmlElement* pXMLData );
    bool loadActor( TiXmlElement* pXMLData );
    void PartitionNavGraph();
    //
    void RectangleWall( gcn::Point supIzq,
                        gcn::Point supDch,
                        gcn::Point infIzq,
                        gcn::Point infDch );

    void Free1Nodes( gcn::Point pMap );
    void Free4Nodes( gcn::Point pMap );
    void Free6Nodes( gcn::Point pMap );
    void FreeNode( gcn::Point pMap );
    void AddWall( gcn::Point from,
                  gcn::Point to );
    void selectActor( CActorMapa* actor );

};

#endif /* PLAYMODEL_H_ */
