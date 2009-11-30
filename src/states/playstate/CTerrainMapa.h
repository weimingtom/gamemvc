/*
 * CTerrainMapa.h
 *
 *  Created on: 29-dic-2008
 *      Author: Administrador
 */

#ifndef CTERRAINMAPA_H_
#define CTERRAINMAPA_H_

#include <game/database/BaseGameEntity.h>
#include <misc/Point.h>

namespace gcn {

	class Graphics;

}

class PlayModel;
class CTile;

class CTerrainMapa: public BaseGameEntity
{
public:

	CTerrainMapa( PlayModel* world );
	virtual ~CTerrainMapa();

	void SetTile(CTile* tile, const CPoint& p);

	void Draw( 	gcn::Graphics* graphics,
				int destX,
				int destY );

private:

	PlayModel* m_pModel;
	CTile* m_pTerrain;

};

#endif /* CTERRAINMAPA_H_ */
