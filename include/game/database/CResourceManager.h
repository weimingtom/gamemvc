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
#include <boost/shared_ptr.hpp>

#include <misc/singleton.hpp>

class CResourceType;
class TiXmlElement;

#define ResourceManager	Singleton<CResourceManager>::Instance()

class CResourceManager
{
  public:

    bool ResourceExist( const std::string& elResource ) const;
    CResourceType* GetResourceType( const std::string& elResource );
    bool Load( TiXmlElement* pXMLData );

  private:

    typedef boost::shared_ptr < CResourceType > CResourceType_ptr;
    typedef std::map < std::string, CResourceType_ptr > CResourceType_map;

    CResourceType_map m_mResourceManager;
};

#endif /* CRESOURCEMANAGER_H_ */
