/*
 * PlayController.cpp
 *
 *  Created on: 04/01/2010
 *      Author: 79481180
 */

#include "PlayController.h"

#include "PlayView.h"
#include "PlayModel.h"

PlayController::PlayController( PlayView* view ) :
	Controller < PlayModel, PlayView > ( view ) {

}

PlayController::~PlayController() {

}
void PlayController::keyPressed( gcn::KeyEvent& keyEvent ) {

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

		case gcn::Key::F1:
			View().CreateMap( IMap::ISO_DIAMOND_MAP_TYPE );
			break;
		case gcn::Key::F2:
			View().CreateMap( IMap::ISO_SLIDE_MAP_TYPE );
			break;
		case gcn::Key::F3:
			View().CreateMap( IMap::ISO_STAGGERED_MAP_TYPE );
			break;
		case gcn::Key::F4:
			View().CreateMap( IMap::HEX_DIAMOND_MAP_TYPE );
			break;
		case gcn::Key::F5:
			View().CreateMap( IMap::HEX_SLIDE_MAP_TYPE );
			break;
		case gcn::Key::F6:
			View().CreateMap( IMap::HEX_STAGGERED_MAP_TYPE );
			break;
		case gcn::Key::F7:
			View().CreateMap( IMap::SQUARED_MAP_TYPE );
			break;
		case '8':
			View().MoveCursor( IMap::NORTH );
			break;
		case '9':
			View().MoveCursor( IMap::NORTH_EAST );
			break;
		case '6':
			View().MoveCursor( IMap::EAST );
			break;
		case '3':
			View().MoveCursor( IMap::SOUTH_EAST );
			break;
		case '2':
			View().MoveCursor( IMap::SOUTH );
			break;
		case '1':
			View().MoveCursor( IMap::SOUTH_WEST );
			break;
		case '4':
			View().MoveCursor( IMap::WEST );
			break;
		case '7':
			View().MoveCursor( IMap::NORTH_WEST );
			break;

		default:
			;

	}
	keyEvent.consume();
}
void PlayController::mouseMoved( gcn::MouseEvent& mouseEvent ) {

	//grab mouse coordinate

	View().MoveMouse( 	mouseEvent.getX(),
						mouseEvent.getY() );

	mouseEvent.consume();

}
