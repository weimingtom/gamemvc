/*
 * PlayViewMsgCenter.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "PlayViewMsgCenter.h"

#include <xmlgui.h>

#include <misc/Interface.h>
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
		m_interface_(Model().interface()),
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
	m_interface_.screen().getGraphics()->pushClipArea( m_pos );
	m_interface_.screen().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
	m_interface_.screen().getGraphics()->drawLine(	10,
											10,
											100,
											100 );
	m_interface_.screen().getGraphics()->drawText(	"Otro texto de prueba",
											15,
											15 );
	m_interface_.screen().getGraphics()->popClipArea();

}
