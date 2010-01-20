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
		m_msgcenter( xmlgui.getWidget( "msgcenter" ) ),
		m_pos(m_msgcenter->getClipRectangle()){

	std::cout <<"Dimension :   " << m_msgcenter->getDimension() << std::endl;
	std::cout <<"ChildrenArea: " << m_msgcenter->getChildrenArea() << std::endl;
	std::cout <<"Pos:          " << m_pos << std::endl;

}
void PlayViewMsgCenter::initialize() {

	setController( new PlayControllerMsgCenter( this ) );
	m_msgcenter->addMouseListener( &Controller() );

}
void PlayViewMsgCenter::draw() {

	//
	// Pintamos la parte del MsgCenter
	//
	Model().game().getGui().getGraphics()->pushClipArea( m_pos );
	Model().game().getGui().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
	Model().game().getGui().getGraphics()->drawLine(	10,
											10,
											100,
											100 );
	Model().game().getGui().getGraphics()->drawText(	"Otro texto de prueba",
											15,
											15 );
	Model().game().getGui().getGraphics()->popClipArea();

}
