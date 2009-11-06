/*
 * CResourceManager.h
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#ifndef CRESOURCEMANAGER_H_
#define CRESOURCEMANAGER_H_

#include <string>
#include <map>
using namespace std;

#include <misc/Singleton.h>

class CResourceType;
class TiXmlElement;

#define ResourceManager	Singleton<CResourceManager>::GetSingletonPtr()

class CResourceManager
{
public:

	virtual ~CResourceManager();
	CResourceType*	GetResourceType(string elResource);
	bool 			Load(TiXmlElement* pXMLData);

private:

	map<string , CResourceType* > 	m_mResourceManager;
};

#endif /* CRESOURCEMANAGER_H_ */
