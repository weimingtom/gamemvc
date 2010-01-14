/*
 * CFrame.h
 *
 *  Created on: 11/12/2009
 *      Author: 79481180
 */

#ifndef CFRAME_H_
#define CFRAME_H_

#include <utility>
#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

class TiXmlElement;
namespace gcn {

	class Graphics;
	class Image;

}

class CFrame
{
public:

	bool Load( TiXmlElement* pXMLData );
	void Draw( 	gcn::Graphics* graphics,
				int destX,
				int destY ) const;

private:

	typedef boost::shared_ptr < gcn::Image > Image_ptr;

	std::pair < Image_ptr, gcn::Point > m_Frame;

};

#endif /* CFRAME_H_ */
