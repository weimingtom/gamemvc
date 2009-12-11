/*
 * CActorMapaManager.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CACTORMAPAMANAGER_H_
#define CACTORMAPAMANAGER_H_

#include <vector>
using namespace std;

class TiXmlElement;
class CActorMapa;
class GameWorld;

class CActorMapaManager {
public:

	CActorMapaManager(GameWorld* pWorld);
	~CActorMapaManager();

	bool 		Load(TiXmlElement* pXMLData);

	vector<CActorMapa*>& _getActors();

private:

	GameWorld*						m_pWorld;
	vector<CActorMapa*>				m_ActorMapa;

};

#endif /* CACTORMAPAMANAGER_H_ */
