/*
 * CBuildingMapa.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CBUILDINGMAPA_H_
#define CBUILDINGMAPA_H_

#include <guichan.hpp>

#include <game/BaseGameEntity.h>

class TiXmlElement;
class CBuildingType;
class PlayModel;

class CBuildingMapa: public BaseGameEntity
{
public:

	CBuildingMapa( PlayModel* model );

	bool Load( TiXmlElement* pXMLData );

	void Draw( 	gcn::Graphics* graphics,
				int destX,
				int destY )const;

private:

	PlayModel* m_pModel; //!
	const CBuildingType* m_pBuildingType; //! Tipo de building


};

#endif /* CBUILDINGMAPA_H_ */
