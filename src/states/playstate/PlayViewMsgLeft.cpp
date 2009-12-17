/*
 * PlayViewMsgLeft.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "PlayViewMsgLeft.h"

#include <sstream>
#include <xmlgui.h>

#include <MyGame.h>

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayControllerMsgLeft.h"

//-------------------------------------------------------------------
//
// PlayViewMsgLeft
//
PlayViewMsgLeft::PlayViewMsgLeft( PlayModel* model, XmlGui& xmlgui ) :
	View < PlayModel, PlayControllerMsgLeft > ( model ),
	m_msgleft( xmlgui.getWidget( "msgleft" )),
	m_name ( static_cast < gcn::TextField* > ( xmlgui.getWidget( "name" ) )),
	m_posX ( static_cast < gcn::TextField* > ( xmlgui.getWidget( "X" ) )),
	m_posY ( static_cast < gcn::TextField* > ( xmlgui.getWidget( "Y" ) )) {

}
void PlayViewMsgLeft::initialize() {

}
void PlayViewMsgLeft::setMsgLeftname(const std::string& name) {

	m_name->setText( name );

}
void PlayViewMsgLeft::setMsgLeftX(const int& X){

	std::stringstream ox;
	ox << X;
	m_posX->setText( ox.str() );

}
void PlayViewMsgLeft::setMsgLeftY(const int& Y){

	std::stringstream oy;
	oy << Y;
	m_posY->setText( oy.str() );

}
void PlayViewMsgLeft::draw() {

}
void PlayViewMsgLeft::resetMsgLeft(){

	m_name->setText( "" );
	m_posX->setText( "" );
	m_posY->setText( "" );

}

