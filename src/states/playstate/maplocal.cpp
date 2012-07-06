/*
 * MapLocal.cpp
 *
 *  Created on: 12/01/2010
 *      Author: 79481180
 */

#include "maplocal.h"

#include <cassert>
#include <isohex/IMouseMap.hpp>

MapLocal::MapLocal( int size ) :
    m_LocalSize( size )
{

}

MapLocal::~MapLocal()
{

}
void MapLocal::setScroller( const ScrollerPtrType& scroller )
{
  ptScroller = scroller.get();
}
gcn::Point MapLocal::LocalToScreen( const Vector2D& local ) const
{

  assert( ptScroller!=NULL );
  // Mouse Map de 1 x 0.5
  gcn::Point desp;
  desp.x = static_cast < int >( local.x ) % m_LocalSize;
  desp.y = static_cast < int >( local.y ) % m_LocalSize;
  gcn::Point p = ptScroller->plot( LocalToMap( local ) )
      - gcn::Point( 0,
                    ptScroller->tileAnchor().y )
      + gcn::Point( ( desp.x - desp.y ) / 2,
                    ( desp.x + desp.y ) / 4 );
  return p;

}
gcn::Point MapLocal::LocalToMap( const Vector2D& local ) const
{

  gcn::Point pMap;
  pMap.x = static_cast < int >( local.x ) / m_LocalSize;
  pMap.y = static_cast < int >( local.y ) / m_LocalSize;
  return pMap;

}
gcn::Point MapLocal::ScreenToLocal( const gcn::Point& pScreen ) const
{
  //
  // Entramos con un punto de la pantalla y salimos con el punto local
  // equivalente.
  // 1� Pasamos el punto de la pantalla a punto del mapa pMap ( Punto isometrico ).
  // 2� Calculamos los delta del pScreen con respecto al pMap.
  // 3� Pasamos el pMap a local y le aplicamos los delta.
  //
  gcn::Point pMap = ptScroller->map( pScreen );
  gcn::Point w = pScreen - ptScroller->plot( pMap );
  gcn::Point p;
  p.x = 2 * w.y + w.x;
  p.y = 2 * w.y - w.x;
  gcn::Point res = MapToLocal < gcn::Point >( pMap ) + p;
  return res;

}
