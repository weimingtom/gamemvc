/*
 * CResourceType.h
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#ifndef CRESOURCETYPE_H_
#define CRESOURCETYPE_H_

#include <string>
#include <guichan.hpp>

class TiXmlElement;
namespace gcn {

  class Graphics;
  class Image;

}
class CResourceType
{
  public:

    virtual ~CResourceType();
    bool Load( TiXmlElement* pXMLData );

    void Draw( gcn::Graphics* graphics,
               int destX,
               int destY ) const;

    int GetSpace() const;

  private:

    std::string m_Name; //!
    int m_iAnchorX; //!
    int m_iAnchorY; //!
    gcn::Image* m_pImage; //!
    gcn::Point m_adjust; //!
    int m_space; //!

};

#endif /* CRESOURCETYPE_H_ */
