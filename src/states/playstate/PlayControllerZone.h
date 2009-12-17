/*
 * PlayControllerZone.h
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#ifndef PLAYCONTROLLERZONE_H_
#define PLAYCONTROLLERZONE_H_

#include <guichan.hpp>
#include <mvc/Controller.h>

class PlayModel;
class PlayViewZone;

class PlayControllerZone: public Controller<PlayModel, PlayViewZone> ,
		public gcn::MouseListener
{
public:

	PlayControllerZone(PlayViewZone* view);
	void mousePressed(gcn::MouseEvent& mouseEvent);
	void mouseDragged(gcn::MouseEvent& mouseEvent);
	void mouseReleased(gcn::MouseEvent& mouseEvent);
	void mouseMoved(gcn::MouseEvent& mouseEvent);
	void mouseWheelMovedDown(gcn::MouseEvent& mouseEvent);
	void mouseWheelMovedUp(gcn::MouseEvent& mouseEvent);
	void mouseEntered(gcn::MouseEvent& mouseEvent);
	void mouseExited(gcn::MouseEvent& mouseEvent);

};

#endif /* PLAYCONTROLLERZONE_H_ */
