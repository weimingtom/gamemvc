/*
 * CStatus.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CSTATUS_H_
#define CSTATUS_H_

#include <map>
#include <string>
using namespace std;
#include <tinyxml.h>

class CDir;

class CStatus {
public:

	~CStatus();
	bool 	Load(TiXmlElement* pXMLData);
	string	GetName(){return m_Name;}
	CDir*	GetDir(string laDir);
	int		GetFrames();

private:

	string	m_Name; 				//!Nombre del estado.
	int		m_iFrames;				//! Contador de cambio de frames.
	map <string, CDir* >	m_mDir;
};

#endif /* CSTATUS_H_ */
