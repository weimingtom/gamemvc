/*
 * CTerrainManager.h
 *
 *  Created on: 12-ago-2008
 *      Author: Administrador
 */

#ifndef CTERRAINMANAGER_H_
#define CTERRAINMANAGER_H_

#include <map>
#include <memory>
#include <string>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <misc/singleton.hpp>

class CTerrainType;
class TiXmlElement;

#define TerrainManager Singleton < CTerrainManager >::Instance()

class CTerrainManager
{
  public:

    bool Load( TiXmlElement* pXMLData );
    bool TerrainExist( const std::string& elTerreno ) const;
    CTerrainType* GetTerrainType( const std::string& elTerreno );

  private:

    typedef boost::shared_ptr < CTerrainType > CTerrainType_ptr;
    typedef std::map < std::string, CTerrainType_ptr > CTerrainType_map;

    CTerrainType_map m_mTerrainManager; //! Mapa todos los tipos de terreno

};

#endif /* CTERRAINMANAGER_H_ */
