/*
 * PlayController.h
 *
 *  Created on: 04/01/2010
 *      Author: 79481180
 */

#ifndef PLAYCONTROLLER_H_
#define PLAYCONTROLLER_H_

#include <guichan.hpp>

#include "mvc/Controller.h"

class PlayView;
class PlayModel;

class PlayController:	public Controller < PlayModel, PlayView > ,
						public gcn::KeyListener,
						public gcn::MouseListener
{
public:

	PlayController(PlayView* view );
	virtual ~PlayController();

	void keyPressed(gcn::KeyEvent& keyEvent);
	void mouseMoved(gcn::MouseEvent& mouseEvent) ;

};

#endif /* PLAYCONTROLLER_H_ */
