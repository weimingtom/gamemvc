/*
 * CMouseMapManager.cpp
 *
 *  Created on: 03-nov-2008
 *      Author: 79481180
 */
#include "CMouseMapManager.h"

#include <cassert>

void CMouseMapManager::Init( const std::string& fileName ) {

	m_pMouseMap.reset( new MouseMap( fileName ) );

}
MouseMap* CMouseMapManager::GetMouseMap() {

	assert(m_pMouseMap.get());
	return m_pMouseMap.get();

}
