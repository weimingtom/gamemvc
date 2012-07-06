/*
 * CDir.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CDIR_H_
#define CDIR_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class TiXmlElement;
class CFrame;

class CDir
{
  public:

    typedef boost::shared_ptr < CFrame > CFrame_ptr;

    bool Load( TiXmlElement* pXMLData );
    CFrame* GetFrame( const int& numImage );
    int GetMaxFrames() const;

  private:

    std::vector < CFrame_ptr > m_Frame;

};

#endif /* CDIR_H_ */
