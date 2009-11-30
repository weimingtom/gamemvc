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
#include "mvc/Model.h"
#include "misc/Point.h"

#include "CellMapaPartition.h"
#include "CTerrainMapaManager.h"
#include "CBuildingMapaManager.h"

class TiXmlElement;

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

	PlayModel();
	virtual ~PlayModel();

	bool isEnd();
	void setEnd( const PlayModel::EndTypes& type );
	PlayModel::EndTypes getEnd() const;

	int getResolution();
	int getTopPadding();

	CellPartition* const GetCellPartition() const;

	Vector2D IsoToLocal( 	int ix,
							int iy ); //! Utilizado por ActorMapaManager
	Vector2D IsoToLocal( Vector2D p );
	CPoint IsoToLocal( CPoint p );

	void Update();

	std::vector < CTerrainMapa* > ObtainTerrainCell( const CPoint& pLocal );
	std::vector < CBuildingMapa* > ObtainBuildingCell( const CPoint& pLocal );


private:

	PlayModel::EndTypes m_endtype;

	std::string m_sMapName;
	int m_iResolution;
	int m_iTopPadding;

	int m_iSizeX;
	int m_iSizeY;

	int m_iCellsX;
	int m_iCellsY;

	std::auto_ptr < CellPartition > m_pCellPartition; //! Division del mapa isometrico?.

	typedef std::auto_ptr < CTerrainMapaManager > CTerrainMapaManager_ptr;
	typedef std::auto_ptr < CBuildingMapaManager > CBuildingMapaManager_ptr;

	CTerrainMapaManager_ptr m_pTerrainMapaManager;
	CBuildingMapaManager_ptr m_pBuildingMapaManager;

	void loadGame( const std::string& mapData );
	bool loadXML( TiXmlElement* pXMLData );
	//
	bool loadTerrain( TiXmlElement* pXMLData );
	bool loadBuilding( TiXmlElement* pXMLData );

};

#endif /* PLAYMODEL_H_ */
