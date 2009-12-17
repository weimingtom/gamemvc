/*
 * PlayViewMsgCenter.h
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#ifndef PLAYVIEWMSGCENTER_H_
#define PLAYVIEWMSGCENTER_H_

#include <guichan.hpp>
#include <mvc/View.h>

class PlayControllerMsgCenter;
class PlayModel;
class PlayView;
class XmlGui;

class PlayViewMsgCenter : public View < PlayModel, PlayControllerMsgCenter >
{
public:

	PlayViewMsgCenter( PlayModel* model, XmlGui& xmlgui );
	void initialize();
	void draw();

private:

	gcn::Widget* m_msgcenter;

};

#endif /* PLAYVIEWMSGCENTER_H_ */
