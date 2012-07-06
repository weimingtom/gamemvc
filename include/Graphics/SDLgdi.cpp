/*
 * SDLgdi.cpp
 *
 *  Created on: 08-ago-2008
 *      Author: 79481180
 */

#include "SDLgdi.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

SDLgdi* SDLgdi::m_pInstance = NULL;
//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
SDLgdi* SDLgdi::Instance()
{

  return m_pInstance;

}
//ALWAYS call this before drawing
SDLgdi::SDLgdi( gcn::Graphics* hdc,
                const ScrollerPtrType& scroller,
                const MapLocal& map )
    : m_ActPen( gcn::Color::Red ),
      m_hdc( hdc ),
      m_Scroller_( scroller ),
      m_map_( map )
{

  m_pInstance = this;

}
SDLgdi::~SDLgdi()
{
  m_pInstance = NULL;
}

void SDLgdi::SetPenColor( const gcn::Color& color )
{
  m_ActPen = color;
}
void SDLgdi::ClosedShapeISO( const std::vector < Vector2D > &points )
{
  double x = points[0].x;
  double y = points[0].y;
  double x1;
  double y1;
  DrawDotISO( (Sint16) x,
              (Sint16) y,
              m_ActPen );
  for ( unsigned int p = 1; p < points.size(); ++p ) {
    double x1 = points[p].x;
    double y1 = points[p].y;
    LineISO( x,
             y,
             x1,
             y1 );
    x = points[p].x;
    y = points[p].y;
  }
  x1 = points[0].x;
  y1 = points[0].y;
  LineISO( x,
           y,
           x1,
           y1 );
}
void SDLgdi::DrawDotISO( int x,
                         int y,
                         gcn::Color color )
{
  gcn::Point p( LocalToScreen( Vector2D( x,
                                         y ) ) );

  gcn::Color c = m_hdc->getColor();
  m_hdc->setColor( color );
  m_hdc->drawPoint( p.x,
                    p.y );
  m_hdc->setColor( c );

}
void SDLgdi::LineISO( int a,
                      int b,
                      int x,
                      int y )
{

  LineISO( Vector2D( a,
                     b ),
           Vector2D( x,
                     y ) );

}
void SDLgdi::LineISO( Vector2D from,
                      Vector2D to )
{

  gcn::Point p1 = LocalToScreen( from );
  gcn::Point p2 = LocalToScreen( to );
  gcn::Color c = m_hdc->getColor();
  m_hdc->setColor( m_ActPen );
  m_hdc->drawLine( p1.x,
                   p1.y,
                   p2.x,
                   p2.y );
  m_hdc->setColor( c );
}
void SDLgdi::CircleISO( Vector2D pos,
                        double radius )
{

  gcn::Point ejes( lround( radius * 0.70710678118655 ),
                   lround( radius * 0.35355339059327 ) );

  this->Ellipse( LocalToScreen( pos ),
                 ejes,
                 m_ActPen );
}
void SDLgdi::TextAtPosISO( int x,
                           int y,
                           const std::string& s,
                           gcn::Color color )
{

  gcn::Point p = LocalToScreen( Vector2D( x,
                                          y ) );
  gcn::Color c = m_hdc->getColor();
  m_hdc->setColor( color );
  m_hdc->drawText( s,
                   p.x,
                   p.y,
                   gcn::Graphics::LEFT );
  m_hdc->setColor( c );

}
/*
 void SDLgdi::Cross( Vector2D pos,
 int diameter ) {
 Line( (int) pos.x - diameter,
 (int) pos.y - diameter,
 (int) pos.x + diameter,
 (int) pos.y + diameter );
 Line( (int) pos.x - diameter,
 (int) pos.y + diameter,
 (int) pos.x + diameter,
 (int) pos.y - diameter );
 }
 void SDLgdi::CrossISO( Vector2D pos,
 int diameter ) {
 LineISO( (int) pos.x - diameter,
 (int) pos.y - diameter,
 (int) pos.x + diameter,
 (int) pos.y + diameter );
 LineISO( (int) pos.x - diameter,
 (int) pos.y + diameter,
 (int) pos.x + diameter,
 (int) pos.y - diameter );
 }
 //----------------------------pixels
 void SDLgdi::DrawDot( Vector2D pos,
 gcn::Color color ) {
 m_hdc->SetPixel( (Sint16) pos.x,
 (Sint16) pos.y,
 color );
 }
 void SDLgdi::DrawDot( CPoint pos,
 gcn::Color color ) {
 m_hdc->SetPixel( pos.X(),
 pos.Y(),
 color );
 }

 void SDLgdi::DrawDotISO( Vector2D pos,
 gcn::Color color ) {
 DrawDot( m_pView->LocalToScreen( pos ),
 color );
 }

 //-------------------------Line Drawing

 void SDLgdi::Line( Vector2D from,
 Vector2D to ) {
 Line( from.x,
 from.y,
 to.x,
 to.y );
 }

 void SDLgdi::Line( int a,
 int b,
 int x,
 int y ) {
 m_hdc->Line( (Sint16) a,
 (Sint16) b,
 (Sint16) x,
 (Sint16) y,
 m_ActPen );
 }

 void SDLgdi::Line( double a,
 double b,
 double x,
 double y ) {
 Line( (Sint16) a,
 (Sint16) b,
 (Sint16) x,
 (Sint16) y );
 }
 void SDLgdi::LineISO( Vector2D from,
 Vector2D to ) {

 CPoint p1 = m_pView->LocalToScreen( from );
 CPoint p2 = m_pView->LocalToScreen( to );

 m_hdc->Line( m_pView->LocalToScreen( from ),
 m_pView->LocalToScreen( to ),
 m_ActPen );
 }

 void SDLgdi::LineISO( double a,
 double b,
 double x,
 double y ) {
 LineISO( (int) a,
 (int) b,
 (int) x,
 (int) y );
 }

 //---------------------Geometry drawing methods

 void SDLgdi::Rect( int left,
 int top,
 int right,
 int bot ) {
 m_hdc->Rect( (Sint16) left,
 (Sint16) top,
 (Sint16) right,
 (Sint16) bot,
 m_ActPen );
 }
 void SDLgdi::Rect( double left,
 double top,
 double right,
 double bot ) {
 Rect( (Sint16) left,
 (Sint16) top,
 (Sint16) right,
 (Sint16) bot );
 }
 void SDLgdi::RectISO( int left,
 int top,
 int right,
 int bot ) {
 LineISO( left,
 top,
 right,
 top );
 LineISO( right,
 top,
 right,
 bot );
 LineISO( right,
 bot,
 left,
 bot );
 LineISO( left,
 bot,
 left,
 top );
 }
 void SDLgdi::RectISO( double left,
 double top,
 double right,
 double bot ) {
 LineISO( left,
 top,
 right,
 top );
 LineISO( right,
 top,
 right,
 bot );
 LineISO( right,
 bot,
 left,
 bot );
 LineISO( left,
 bot,
 left,
 top );
 }
 void SDLgdi::ClosedShape( const std::vector < Vector2D > &points ) {
 Sint16 x = (Sint16) points[0].x;
 Sint16 y = (Sint16) points[0].y;
 DrawDot( (Sint16) x,
 (Sint16) y,
 m_ActPen );
 for ( unsigned int p = 1; p < points.size(); ++p ) {
 Line( (Sint16) x,
 (Sint16) y,
 (Sint16) points[p].x,
 (Sint16) points[p].y );
 x = (Sint16) points[p].x;
 y = (Sint16) points[p].y;
 }
 Line( (Sint16) x,
 (Sint16) y,
 (Sint16) points[0].x,
 (Sint16) points[0].y );
 }

 void SDLgdi::Circle( Vector2D pos,
 double radius ) {
 m_hdc->Circle( (Sint16) pos.x,
 (Sint16) pos.y,
 (Sint16) radius,
 m_ActPen );
 }

 void SDLgdi::Circle( double x,
 double y,
 double radius ) {
 Circle( (Sint16) x,
 (Sint16) y,
 (Sint16) radius );
 }

 void SDLgdi::Circle( int x,
 int y,
 double radius ) {
 Circle( (Sint16) x,
 (Sint16) y,
 (Sint16) radius );
 }


 */
//-------------------------------------------------------------------------------
//
// Funciones privadas.
//-------------------------------------------------------------------------------
gcn::Point SDLgdi::LocalToScreen( const Vector2D& pLocal ) const
{

  gcn::Point pScreen = m_map_.LocalToScreen( pLocal );
  return pScreen;
}
void SDLgdi::DrawDot( gcn::Point pos,
                      gcn::Color color )
{

  gcn::Color c = m_hdc->getColor();
  m_hdc->setColor( color );
  m_hdc->drawPoint( pos.x,
                    pos.y );
  m_hdc->setColor( c );

}
void SDLgdi::DrawDot( int x,
                      int y,
                      gcn::Color color )
{

  gcn::Color c = m_hdc->getColor();
  m_hdc->setColor( color );
  m_hdc->drawPoint( x,
                    y );
  m_hdc->setColor( c );

}
void SDLgdi::Ellipse( gcn::Point p,
                      gcn::Point r,
                      const gcn::Color& color )
{

  gcn::Color c = m_hdc->getColor();
  m_hdc->setColor( color );
  m_hdc->drawEllipse( p.x,
                      p.y,
                      r.x,
                      r.y );
  m_hdc->setColor( c );

}
