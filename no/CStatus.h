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
#include <tinyxml.h>

class CDir;

class CStatus
{
public:

	~CStatus();
	bool Load( TiXmlElement* pXMLData );
	string GetName() {
		return m_Name;
	}
	CDir* GetDir( std::string& laDir );
	int GetFrames();

private:

	std::string m_Name; //!Nombre del estado.
	int m_iFrames; //! Contador de cambio de frames.
	map < std::string, CDir* > m_mDir;
};

#endif /* CSTATUS_H_ */
