/*
 * CMouseMapManager.h
 *
 *  Created on: 03-nov-2008
 *      Author: 79481180
 */

#ifndef CMOUSEMAPMANAGER_H_
#define CMOUSEMAPMANAGER_H_

#include <string>

#include <boost/utility.hpp>

#include <misc/Singleton.hpp>

#include "MouseMap.hpp"

#define MouseMapManager	Singleton < CMouseMapManager >::instance()
#define mouse MouseMapManager.GetMouseMap()

class CMouseMapManager
{

public:

	void Init( const std::string &fileName );
	MouseMap* GetMouseMap();

private:

	std::auto_ptr < MouseMap > m_pMouseMap;

};

#endif /* CMOUSEMAPMANAGER_H_ */
