/*
 * SDLgdi.h
 *
 *  Created on: 08-ago-2008
 *      Author: 79481180
 */

#ifndef SDLGDI_H_
#define SDLGDI_H_

#include <string>
#include <vector>
#include <cassert>

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <isohex/Scroller.hpp>

#include <2d/Vector2D.h>

#include "states/playstate/maplocal.h"

//make life easier on the fingers
#define gdi SDLgdi::Instance()

class MapLocal;

class SDLgdi
{
  public:

    SDLgdi( gcn::Graphics* hdc,
            const ScrollerPtrType& scroller,
            const MapLocal& map );
    virtual ~SDLgdi();
    static SDLgdi* Instance();

    void SetPenColor( const gcn::Color& color );

    void ClosedShapeISO( const std::vector < Vector2D > &points );
    void DrawDotISO( int x,
                     int y,
                     gcn::Color color );
    void LineISO( int a,
                  int b,
                  int x,
                  int y );
    void LineISO( Vector2D from,
                  Vector2D to );
    void CircleISO( Vector2D pos,
                    double radius );

    void TextAtPosISO( int x,
                       int y,
                       const std::string& s,
                       gcn::Color color );
    /*
     void Cross(Vector2D pos, int diameter);
     void CrossISO(Vector2D pos, int diameter);

     void DrawDot(Vector2D pos, gcn::Color color);

     void DrawDotISO(Vector2D pos, gcn::Color color);
     void DrawDotISO(int x, int y, gcn::Color color);

     void Line(Vector2D from, Vector2D to);
     void Line(int a, int b, int x, int y);
     void Line(double a, double b, double x, double y);



     void LineISO(double a, double b, double x, double y);

     void Rect(int left, int top, int right, int bot);
     void Rect(double left, double top, double right, double bot);

     void RectISO(int left, int top, int right, int bot);
     void RectISO(double left, double top, double right, double bot);

     void ClosedShape(const std::vector<Vector2D> &points);



     void Circle(Vector2D pos, double radius);
     void Circle(double x, double y, double radius);
     void Circle(int x, int y, double radius);

     void CircleISO(Vector2D pos, double radius);


     */

  private:

    gcn::Color m_ActPen;

    gcn::Graphics* m_hdc;
    const ScrollerPtrType& m_Scroller_;
    const MapLocal& m_map_;

    gcn::Point LocalToScreen( const Vector2D& pLocal ) const;
    void DrawDot( int x,
                  int y,
                  gcn::Color color );
    void DrawDot( gcn::Point pos,
                  gcn::Color color );
    void Ellipse( gcn::Point p,
                  gcn::Point r,
                  const gcn::Color& color );

    static SDLgdi* m_pInstance;

    //copy ctor and assignment should be private
    SDLgdi( const SDLgdi& );
    SDLgdi& operator=( const SDLgdi& );

};

#endif /* SDLGDI_H_ */
