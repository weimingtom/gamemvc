/*
 * CResourceMapa.h
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#ifndef CRESOURCEMAPA_H_
#define CRESOURCEMAPA_H_

#include <misc/Point.h>
#include "game/database/BaseGameEntity.h"

class TiXmlElement;
class CResourceType;
class PlayModel;
namespace gcn{
	class Graphics;
}
class CResourceMapa: public BaseGameEntity
{
public:

	CResourceMapa( PlayModel* model );

	bool Load( TiXmlElement* pXMLData );

	void Draw( 	gcn::Graphics* graphics,
				int destX,
				int destY );

private:

	PlayModel* 		m_pModel; //!
	CResourceType* 	m_pResourceType; //! Tipo de resource

};

#endif /* CRESOURCEMAPA_H_ */
