/*
 * PlayController.h
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#ifndef PLAYCONTROLLER_H_
#define PLAYCONTROLLER_H_

#include <guichan.hpp>

#include "mvc/Controller.h"

class PlayView;
class PlayModel;

class PlayController:	public Controller < PlayModel, PlayView > ,
						public gcn::KeyListener
{
public:

	PlayController( PlayView* view );
	virtual ~PlayController();
	gcn::MouseListener* getZoneMouseListener();
	gcn::MouseListener* getMsgCenterMouseListener();

private:

	class Zone: public gcn::MouseListener
	{
	public:

		Zone( PlayController* play );
		void mousePressed( gcn::MouseEvent& mouseEvent );
		void mouseDragged( gcn::MouseEvent& mouseEvent );
		void mouseReleased( gcn::MouseEvent& mouseEvent );
		void mouseMoved( gcn::MouseEvent& mouseEvent );
		void mouseWheelMovedDown( gcn::MouseEvent& mouseEvent );
		void mouseWheelMovedUp( gcn::MouseEvent& mouseEvent );
		void mouseEntered( gcn::MouseEvent& mouseEvent );
		void mouseExited( gcn::MouseEvent& mouseEvent );

	private:

		PlayController* m_play;

	} zoneMouseListener;

	class MsgCenter: public gcn::MouseListener
	{
	public:

		MsgCenter( PlayController* play );
		void mouseMoved( gcn::MouseEvent& mouseEvent );
		void mouseEntered( gcn::MouseEvent& mouseEvent );
		void mouseExited( gcn::MouseEvent& mouseEvent );

	private:

		PlayController* m_play;

	} msgcenterMouseListener;

	void keyPressed( gcn::KeyEvent& keyEvent );

};

#endif /* PLAYCONTROLLER_H_ */
