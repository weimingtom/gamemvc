/*
 * CBuildingType.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CBUILDINGTYPE_H_
#define CBUILDINGTYPE_H_

#include <string>
using namespace std;

#include <SDL++/Point.h>

class TiXmlElement;
class CImage;
class CCanvas;
class CPoint;

class CBuildingType {
public:

	~CBuildingType();

	bool			Load(TiXmlElement* pXMLData);
	string 			GetNameBuildingType();
	void 			Draw(CCanvas* pDestSurface, CPoint puntoDest);
	int				GetSpace();

private:
	string			m_Name;			//!
	int				m_iAnchorX;		//!
	int				m_iAnchorY;		//!
	CImage*			m_pImage;		//!
	CPoint			m_adjust;		//!
	int				m_space;		//!
};

#endif /* CBUILDINGTYPE_H_ */
