/*
 * CResourceMapaManager.h
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#ifndef CRESOURCEMAPAMANAGER_H_
#define CRESOURCEMAPAMANAGER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class TiXmlElement;
class CResourceMapa;
class PlayModel;

class CResourceMapaManager
{
  public:

    typedef boost::shared_ptr < CResourceMapa > CResourceMapa_ptr;

    CResourceMapaManager( PlayModel* model );

    bool Load( TiXmlElement* pXMLData );

  private:

    PlayModel* m_pModel;
    std::vector < CResourceMapa_ptr > m_ResourceMapa;

};

#endif /* CRESOURCEMAPAMANAGER_H_ */
