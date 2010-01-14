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
	Controller < PlayModel, PlayViewZone > ( view ) {

}
void PlayControllerZone::mouseClicked( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseClicked" << std::endl;
	mouseEvent.consume();
}
void PlayControllerZone::mousePressed( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mousePressed" << std::endl;
	switch (mouseEvent.getButton()){
		case gcn::MouseEvent::LEFT:
			break;
		case gcn::MouseEvent::RIGHT:
			break;
		default:
			break;
	}
	Model().setMouse(	"ZoneX",
							mouseEvent.getX(),
							mouseEvent.getY() );
	View().setPressedMouse( mouseEvent.getX(),
								mouseEvent.getY() );
	mouseEvent.consume();
}
void PlayControllerZone::mouseDragged( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseDragged" << std::endl;
	Model().setMouse(	"ZoneE",
							mouseEvent.getX(),
							mouseEvent.getY() );
	View().setDraggedMouse( mouseEvent.getX(),
								mouseEvent.getY() );
	mouseEvent.consume();
}
void PlayControllerZone::mouseReleased( gcn::MouseEvent& mouseEvent ) {

	std::cout << "mouseReleased" << std::endl;
	Model().setMouse(	"ZoneO",
							mouseEvent.getX(),
							mouseEvent.getY() );
	View().setReleasedMouse( 	mouseEvent.getX(),
									mouseEvent.getY() );
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
