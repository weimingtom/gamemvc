/*
 * MapLocal.h
 *
 *  Created on: 12/01/2010
 *      Author: 79481180
 */

#ifndef MAPLOCAL_H_
#define MAPLOCAL_H_

#include <guichan/point.hpp>
#include <isohex/Scroller.hpp>
#include <2d/Vector2D.h>

class MapLocal
{
  public:

    MapLocal( int size );
    virtual ~MapLocal();

    template < class T >
    T MapToLocal( const gcn::Point& pMap ) const
    {

      T pLocal;

      pLocal.x = pMap.x * m_LocalSize + m_LocalSize / 2;
      pLocal.y = pMap.y * m_LocalSize + m_LocalSize / 2;

      return pLocal;
    }
    void setScroller( const ScrollerPtrType& scroller );
    /**!
     *
     * @param local
     * @return
     */
    gcn::Point LocalToScreen( const Vector2D& local ) const;
    /**!
     *
     * @param local
     * @return
     */
    gcn::Point LocalToMap( const Vector2D& local ) const;
    gcn::Point ScreenToLocal( const gcn::Point& pScreen ) const;
    int getSize() const
    {
      return m_LocalSize;
    }

  private:

    int m_LocalSize;
    Scroller* ptScroller;

};

#endif /* MAPLOCAL_H_ */
