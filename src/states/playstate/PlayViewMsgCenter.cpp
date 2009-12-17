/*
 * PlayViewMsgCenter.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "PlayViewMsgCenter.h"

#include <xmlgui.h>

#include <MyGame.h>

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayControllerMsgCenter.h"

//-------------------------------------------------------------------
//
// PlayViewMsgCenter
//
PlayViewMsgCenter::PlayViewMsgCenter( PlayModel* model, XmlGui& xmlgui ) :
		View < PlayModel, PlayControllerMsgCenter > ( model ),
		m_msgcenter( xmlgui.getWidget( "msgcenter" ) ) {

}
void PlayViewMsgCenter::initialize() {

	m_controller = new PlayControllerMsgCenter( this );
	m_msgcenter->addMouseListener( m_controller );

}
void PlayViewMsgCenter::draw() {

	//
	// Pintamos la parte del MsgCenter
	//
	game.getGui().getGraphics()->pushClipArea( m_msgcenter->getDimension() );
	game.getGui().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
	game.getGui().getGraphics()->drawLine(	10,
											10,
											100,
											100 );
	game.getGui().getGraphics()->drawText(	"Otro texto de prueba",
											15,
											15 );
	game.getGui().getGraphics()->popClipArea();

}
