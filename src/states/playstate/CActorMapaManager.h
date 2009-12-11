/*
 * CActorMapaManager.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CACTORMAPAMANAGER_H_
#define CACTORMAPAMANAGER_H_

#include <vector>

class TiXmlElement;
class CActorMapa;
class PlayModel;

#include "CActorMapa.h"

class CActorMapaManager
{
public:

	CActorMapaManager( PlayModel* pModel );
	~CActorMapaManager();

	bool Load( TiXmlElement* pXMLData );

	std::vector < CActorMapa* >& _getActors();

private:

	PlayModel* m_pModel;
	std::vector < CActorMapa* > m_ActorMapa;

};

#endif /* CACTORMAPAMANAGER_H_ */
