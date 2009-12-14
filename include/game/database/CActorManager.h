/*
 * CActorManager.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CACTORMANAGER_H_
#define CACTORMANAGER_H_

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <lua.hpp>
#include <misc/singleton.hpp>

class CActorType;
class TiXmlElement;

#define ActorManager	Singleton<CActorManager>::Instance()
class CActorManager
{
public:

	bool Load( TiXmlElement* pXMLData );
	bool ActorExist( const std::string& elActor ) const;
	CActorType* GetActorType( const std::string& elActor );

private:

	typedef boost::shared_ptr < CActorType > CActorType_ptr;
	typedef std::map < std::string, CActorType_ptr > CActorType_map;

	CActorType_map m_mActorManager;

};

#endif /* CACTORMANAGER_H_ */
