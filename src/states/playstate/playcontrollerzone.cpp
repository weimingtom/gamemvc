/*
 * PlayControllerZone.cpp
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#include "playcontrollerzone.h"

#include "playmodel.h"
#include "playview.h"
#include "playviewzone.h"

//-------------------------------------------------------------------
PlayControllerZone::PlayControllerZone( PlayViewZone* view ) :
    Controller < PlayModel, PlayViewZone >( view )
{

}
void PlayControllerZone::mousePressed( gcn::MouseEvent& mouseEvent )
{

  model().setMouse( "ZoneX",
                    mouseEvent.getX(),
                    mouseEvent.getY() );

  m_firstselect.x = mouseEvent.getX();
  m_firstselect.y = mouseEvent.getY();

  m_selectarea.x = m_firstselect.x;
  m_selectarea.y = m_firstselect.y;
  m_selectarea.width = 0;
  m_selectarea.height = 0;

  mouseEvent.consume();

}
void PlayControllerZone::mouseDragged( gcn::MouseEvent& mouseEvent )
{

  model().setMouse( "ZoneE",
                    mouseEvent.getX(),
                    mouseEvent.getY() );

  adjustSelectedArea( mouseEvent.getX(),
                      mouseEvent.getY() );

  view().paintSelectedArea( m_selectarea );
  mouseEvent.consume();
}
void PlayControllerZone::mouseReleased( gcn::MouseEvent& mouseEvent )
{

  model().setMouse( "ZoneO",
                    mouseEvent.getX(),
                    mouseEvent.getY() );

  //
  // Tenemos un area para seleccionar.
  adjustSelectedArea( mouseEvent.getX(),
                      mouseEvent.getY() );

  switch ( mouseEvent.getButton() )
  {
    case gcn::MouseEvent::LEFT:
      view().setSelectedArea( m_selectarea );
      break;
    case gcn::MouseEvent::RIGHT:
      view().setDestination( m_selectarea );
      break;
    default:
      break;
  }

  mouseEvent.consume();
}
void PlayControllerZone::mouseMoved( gcn::MouseEvent& mouseEvent )
{

  model().setMouse( "Zone",
                    mouseEvent.getX(),
                    mouseEvent.getY() );
  view().updateMoveView( mouseEvent.getX(),
                         mouseEvent.getY() );
  mouseEvent.consume();

}
void PlayControllerZone::mouseEntered( gcn::MouseEvent& mouseEvent )
{

  model().setMouse( "Zone",
                    mouseEvent.getX(),
                    mouseEvent.getY() );
  view().updateMoveView( mouseEvent.getX(),
                         mouseEvent.getY() );
  mouseEvent.consume();

}
void PlayControllerZone::mouseWheelMovedDown( gcn::MouseEvent & mouseEvent )
{

  model().setMouse( "Zone",
                    mouseEvent.getX(),
                    mouseEvent.getY() );
  view().moveView( 0,
                   +10 );
  mouseEvent.consume();
}
void PlayControllerZone::mouseWheelMovedUp( gcn::MouseEvent & mouseEvent )
{

  model().setMouse( "Zone",
                    mouseEvent.getX(),
                    mouseEvent.getY() );
  view().moveView( 0,
                   -10 );
  mouseEvent.consume();
}
void PlayControllerZone::mouseExited( gcn::MouseEvent& mouseEvent )
{

  model().resetMouse();
  view().resetMove();
  mouseEvent.consume();

}
void PlayControllerZone::keyPressed( gcn::KeyEvent& keyEvent )
{

  switch ( keyEvent.getKey().getValue() )
  {

    case gcn::Key::LEFT:
      view().Scroll( 1,
                     IMap::WEST );
      break;

    case gcn::Key::RIGHT:
      view().Scroll( 1,
                     IMap::EAST );
      break;

    case gcn::Key::UP:
      view().Scroll( 1,
                     IMap::NORTH );
      break;

    case gcn::Key::DOWN:
      view().Scroll( 1,
                     IMap::SOUTH );
      break;

    default:
      ;

  }
  keyEvent.consume();
}
//-------------------------------------------------------------------------------
//
//	Procedimientos privados.
//
//-------------------------------------------------------------------------------
void PlayControllerZone::adjustSelectedArea( int X,
                                             int Y )
{

  int adjX;
  int adjY;
  if ( 0 > X ) {
    adjX = 0;
  } else if ( X > view().area().x + view().area().width - 1 ) {
    adjX = view().area().x + view().area().width - 1;
  } else
    adjX = X;
  if ( 0 > Y ) {
    adjY = 0;
  } else if ( Y > view().area().y + view().area().height - 1 ) {
    adjY = view().area().y + view().area().height - 1;
  } else
    adjY = Y;
  // Tenemos un area para seleccionar.
  m_selectarea.width = std::abs( m_firstselect.x - adjX );
  m_selectarea.height = std::abs( m_firstselect.y - adjY );
  m_selectarea.x = std::min( m_firstselect.x,
                             adjX );
  m_selectarea.y = std::min( m_firstselect.y,
                             adjY );

}
