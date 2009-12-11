/*
 * CTile.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CTILE_H_
#define CTILE_H_

#include <utility>

#include <tinyxml.h>
#include "misc/Point.h"

namespace gcn {

	class Image;
	class Graphics;

}
class CTile
{
public:

	~CTile();

	bool Load( TiXmlElement* pXMLData );
	void Draw( 	gcn::Graphics* graphics,
				int destX,
				int destY );

private:

	std::pair < gcn::Image*, gcn::Point > m_laLoseta; //! Definimos la loseta con su offset.

};

#endif /* CTILE_H_ */
