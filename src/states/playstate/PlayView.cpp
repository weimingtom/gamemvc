/*
 * PlayView.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "PlayView.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <guichan.hpp>
#include <xmlgui.h>

#include <misc/debug.h>

#include <MyGame.h>

#include "PlayModel.h"
#include "PlayController.h"

#include "PlayViewZone.h"
#include "PlayViewMsgLeft.h"
#include "PlayViewMsgCenter.h"

#include "PlayControllerZone.h"
#include "PlayControllerMsgLeft.h"
#include "PlayControllerMsgCenter.h"

PlayView::PlayView( PlayModel* model ) :
	View < PlayModel, PlayController > ( model ) {

	xmlgui.reset( new XmlGui() );
	xmlgui->parse( "./scripts/gui/Play/" + Model().game().getResolution().first
			+ "/gui.xml" );
	Model().game().getGui().setTop( top = xmlgui->getWidget( "top" ) );

	top->requestFocus();

	m_ZoneView.reset( new PlayViewZone( 	model,
										*xmlgui ) );
	m_MsgLeftView.reset( new PlayViewMsgLeft( 	model,
												*xmlgui ) );
	m_MsgCenterView.reset( new PlayViewMsgCenter( 	model,
													*xmlgui ) );

}

PlayView::~PlayView() {

	delete m_MsgCenterView->setController( NULL );
	delete m_MsgLeftView->setController( NULL );
	delete m_ZoneView->setController( NULL );

	Model().game().getGui().setTop(NULL);

}

void PlayView::initialize() {

	setController( new PlayController( this ) );
	top->addKeyListener( &Controller() );

	m_ZoneView->initialize();
	m_MsgLeftView->initialize();
	m_MsgCenterView->initialize();

}

void PlayView::draw() {

	if (Model().ismouse()){

		m_MsgLeftView->setMsgLeftname(Model().getMsgLeftname());
		m_MsgLeftView->setMsgLeftX(Model().getMsgLeftX());
		m_MsgLeftView->setMsgLeftY(Model().getMsgLeftY());

	} else {

		m_MsgLeftView->resetMsgLeft();

	}
	Model().game().getGui().draw();

}
