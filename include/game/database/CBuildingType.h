/*
 * CBuildingType.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CBUILDINGTYPE_H_
#define CBUILDINGTYPE_H_

#include <string>
#include <misc/Point.h>

class TiXmlElement;

namespace gcn {

	class Image;
	class Graphics;

}

class CBuildingType
{
public:

	virtual ~CBuildingType();
	bool Load( TiXmlElement* pXMLData );
	void Draw( 	gcn::Graphics* graphics,
				int destX,
				int destY );

	int GetSpace();

private:

	std::string m_Name;
	int m_iAnchorX;
	int m_iAnchorY;
	gcn::Image* m_pImage;
	gcn::Point m_adjust;
	int m_space;

};

#endif /* CBUILDINGTYPE_H_ */
