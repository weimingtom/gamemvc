/*
 * PlayControllerZone.cpp
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#include "PlayControllerZone.h"

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayViewZone.h"

//-------------------------------------------------------------------
PlayControllerZone::PlayControllerZone( PlayViewZone* view ) :
	Controller < PlayModel, PlayViewZone > ( view ){

}
void PlayControllerZone::mousePressed( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mousePressed" << std::endl;
	Model().setMouse(	"ZoneX",
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
void PlayControllerZone::mouseDragged( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseDragged" << std::endl;
	Model().setMouse(	"ZoneE",
						mouseEvent.getX(),
						mouseEvent.getY() );

	adjustSelectedArea( mouseEvent.getX(), mouseEvent.getY());

	View().paintSelectedArea( m_selectarea );
	mouseEvent.consume();
}
void PlayControllerZone::mouseReleased( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseReleased" << std::endl;
	Model().setMouse(	"ZoneO",
						mouseEvent.getX(),
						mouseEvent.getY() );

	//
	// Tenemos un area para seleccionar.
	adjustSelectedArea( mouseEvent.getX(),
						mouseEvent.getY() );

	View().setSelectedArea( m_selectarea );

	mouseEvent.consume();
}
void PlayControllerZone::mouseMoved( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseMoved" << std::endl;
	Model().setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	View().updateMoveView( 	mouseEvent.getX(),
								mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayControllerZone::mouseEntered( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseEntered" << std::endl;
	Model().setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	View().updateMoveView( 	mouseEvent.getX(),
								mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayControllerZone::mouseWheelMovedDown( gcn::MouseEvent & mouseEvent ) {

	std::cout << "mouseWheelMovedDown" << std::endl;
	Model().setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	View().moveView(	0,
							+10 );
	mouseEvent.consume();
}
void PlayControllerZone::mouseWheelMovedUp( gcn::MouseEvent & mouseEvent ) {

	std::cout << "mouseWheelMovedUp" << std::endl;
	Model().setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	View().moveView(	0,
							-10 );
	mouseEvent.consume();
}
void PlayControllerZone::mouseExited( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseExited" << std::endl;
	Model().resetMouse();
	View().resetMove();
	mouseEvent.consume();

}
void PlayControllerZone::keyPressed( gcn::KeyEvent& keyEvent ) {

	switch ( keyEvent.getKey().getValue() ) {

		case gcn::Key::LEFT:
			View().Scroll( 1,
							IMap::WEST );
			break;

		case gcn::Key::RIGHT:
			View().Scroll( 1,
							IMap::EAST );
			break;

		case gcn::Key::UP:
			View().Scroll( 1,
							IMap::NORTH );
			break;

		case gcn::Key::DOWN:
			View().Scroll( 1,
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
void PlayControllerZone::adjustSelectedArea( 	int X,
												int Y ) {

	int adjX;
	int adjY;
	if ( 0 > X ) {
		adjX = 0;
	} else if ( X > View().area().x + View().area().width - 1 ) {
		adjX = View().area().x + View().area().width - 1;
	} else
		adjX = X;
	if ( 0 > Y ) {
		adjY = 0;
	} else if ( Y > View().area().y + View().area().height - 1 ) {
		adjY = View().area().y + View().area().height - 1;
	} else
		adjY = Y;
	// Tenemos un area para seleccionar.
	m_selectarea.width = std::abs( m_firstselect.x - X );
	m_selectarea.height = std::abs( m_firstselect.y - Y );
	m_selectarea.x = std::min( 	m_firstselect.x,
								X );
	m_selectarea.y = std::min( 	m_firstselect.y,
								Y );

}
