/*
 * MenuModel.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "MenuModel.h"

MenuModel::MenuModel() :
	Model(), m_endtype( MenuModel::CONTINUE ) {

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

