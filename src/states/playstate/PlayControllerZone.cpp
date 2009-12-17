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
void PlayControllerZone::mousePressed( gcn::MouseEvent& mouseEvent ) {

	getModel()->setMouse(	"ZoneX",
							mouseEvent.getX(),
							mouseEvent.getY() );
	getView()->setPressedMouse( 	mouseEvent.getX(),
										mouseEvent.getY() );
	mouseEvent.consume();
}
void PlayControllerZone::mouseDragged( gcn::MouseEvent& mouseEvent ) {

	getModel()->setMouse(	"ZoneE",
							mouseEvent.getX(),
							mouseEvent.getY() );
	getView()->setDraggedMouse( 	mouseEvent.getX(),
										mouseEvent.getY() );
	mouseEvent.consume();
}
void PlayControllerZone::mouseReleased( gcn::MouseEvent& mouseEvent ) {

	getModel()->setMouse(	"ZoneO",
							mouseEvent.getX(),
							mouseEvent.getY() );
	getView()->setReleasedMouse( 	mouseEvent.getX(),
									mouseEvent.getY() );
	mouseEvent.consume();
}
void PlayControllerZone::mouseMoved( gcn::MouseEvent& mouseEvent ) {

	getModel()->setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	getView()->updateMoveView( 	mouseEvent.getX(),
								mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayControllerZone::mouseEntered( gcn::MouseEvent& mouseEvent ) {

	getModel()->setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	getView()->updateMoveView( 	mouseEvent.getX(),
								mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayControllerZone::mouseWheelMovedDown( gcn::MouseEvent & mouseEvent ) {

	getModel()->setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	getView()->moveView(	0,
							+10 );
	mouseEvent.consume();
}
void PlayControllerZone::mouseWheelMovedUp( gcn::MouseEvent & mouseEvent ) {

	getModel()->setMouse(	"Zone",
							mouseEvent.getX(),
							mouseEvent.getY() );
	getView()->moveView(	0,
							-10 );
	mouseEvent.consume();
}
void PlayControllerZone::mouseExited( gcn::MouseEvent& mouseEvent ) {

	getModel()->resetMouse();
	getView()->resetMove();
	mouseEvent.consume();

}
