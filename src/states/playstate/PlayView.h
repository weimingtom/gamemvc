/*
 * PlayView.h
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#ifndef PLAYVIEW_H_
#define PLAYVIEW_H_

#include <memory>
#include <string>
#include <vector>

#include <guichan.hpp>

#include <mvc/View.h>

class PlayModel;
class PlayController;
class PlayViewZone;
class PlayViewMsgLeft;
class PlayViewMsgCenter;

class XmlGui;

class PlayView: public View < PlayModel, PlayController >
{
public:

	PlayView( PlayModel* model );
	virtual ~PlayView();

	void initialize();
	void draw();

	void setMouse(	const std::string& name,
					const int& X,
					const int& Y ) const;
	void resetMouse() const;

private:

	std::auto_ptr < XmlGui > xmlgui;

	gcn::Widget* top;
	std::auto_ptr < PlayViewZone > m_ZoneView;
	std::auto_ptr < PlayViewMsgLeft > m_MsgLeftView;
	std::auto_ptr < PlayViewMsgCenter > m_MsgCenterView;

};

#endif /* PLAYVIEW_H_ */
