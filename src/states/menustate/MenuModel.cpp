/*
 * MenuModel.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "MenuModel.h"

#include <MyGame.h>

MenuModel::MenuModel(MyGame& game) :
	Model(),
	m_game_(game),
	m_endtype( MenuModel::CONTINUE ),
	m_res_(m_game_.interface().actualResolution()){

}

MenuModel::~MenuModel() {

}
void MenuModel::Update() {

}
bool MenuModel::isEnd() {

	return m_endtype != MenuModel::CONTINUE;

}
void MenuModel::setEnd( const MenuModel::EndTypes& type ) {

	m_endtype = type;
}
MenuModel::EndTypes MenuModel::getEnd() const {

	return m_endtype;

}
const Interface& MenuModel::interface() const{

	return m_game_.interface();

}

void MenuModel::changeResolution( const Interface::ScreenResolutionType& res ) {

	m_endtype = MenuModel::CHANGERESOLUTION;
	m_res_ = res;

}
const Interface::ScreenResolutionType& MenuModel::getResolution() const{
	return m_res_;
}
