/*
 * CBuildingManager.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CBUILDINGMANAGER_H_
#define CBUILDINGMANAGER_H_

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <misc/singleton.hpp>

class CBuildingType;
class TiXmlElement;

#define BuildingManager	Singleton<CBuildingManager>::Instance()

class CBuildingManager
{
  public:

    bool Load( TiXmlElement* pXMLData );
    bool BuildingExist( const std::string& elBuilding ) const;
    CBuildingType* GetBuildingType( const std::string& elBuilding );

  private:

    typedef boost::shared_ptr < CBuildingType > CBuildingType_ptr;
    typedef std::map < std::string, CBuildingType_ptr > CBuildingType_map;

    CBuildingType_map m_mBuildingManager;

};

#endif /* CBUILDINGMANAGER_H_ */
