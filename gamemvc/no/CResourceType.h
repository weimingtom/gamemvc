/*
 * CResourceType.h
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#ifndef CRESOURCETYPE_H_
#define CRESOURCETYPE_H_

#include <string>
using namespace std;

#include <SDL++/Point.h>

class TiXmlElement;
class CImage;
class CCanvas;
class CPoint;

class CResourceType
{
public:

	virtual	~CResourceType();
	bool	Load(TiXmlElement* pXMLData);
	string 	GetNameResourceType();
	void 	Draw(CCanvas* pDestSurface, CPoint puntoDest);
	int		GetSpace();

private:
	string	m_Name;			//!
	int		m_iAnchorX;		//!
	int		m_iAnchorY;		//!
	CImage*	m_pImage;		//!
	CPoint	m_adjust;		//!
	int		m_space;		//!
};

#endif /* CRESOURCETYPE_H_ */
