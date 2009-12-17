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

	int celdasX = getModel()->getResolution();
	int celdasY = getModel()->getResolution();
	int pos = 0;
	for (int Y=0;Y<celdasY;Y++){
		for (int X=0;X<celdasX;X++){
			getModel()->GetCellMapa()->GetCell(pos);
			pos++;
		}
	}

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
void PlayViewMsgLeft::resetMsgLeft(){

	m_name->setText( "" );
	m_posX->setText( "" );
	m_posY->setText( "" );

}
void PlayViewMsgLeft::draw() {
	//
	// Obtener todos las celdas del mapa para pintar el minimapa?.
	// Fracamente terriblemente pesado.... a no ser que se ejecute
	// la primera vez, y solo cuando se actualize los elementos del mapa
	// se actualiza la imagen... pero solo de los elementos que se han actualizado.
	//

	int celdasX = getModel()->getResolution();
	int celdasY = getModel()->getResolution();
	int pos = 0;
	for ( int Y = 0; Y < celdasY; Y++ ) {
		for ( int X = 0; X < celdasX; X++ ) {

			CellMapa < BaseGameEntity* > cell =
					getModel()->GetCellMapa()->GetCell( pos );
			std::list < BaseGameEntity* >::iterator iter;
			for ( iter = cell.Members.begin(); iter != cell.Members.end(); ++iter ) {

				BaseGameEntity* base = ( *iter );

			}
			pos++;
		}
	}
}


