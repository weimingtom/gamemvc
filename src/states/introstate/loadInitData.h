/*
 * loadInitData.h
 *
 *  Created on: 18-jun-2009
 *      Author: 79481180
 */

#ifndef LOADINITDATA_H_
#define LOADINITDATA_H_

#include <tinyxml.h>

class TiXmlElement;
class CrtlThread;

class loadInitData
{
public:

	loadInitData( CrtlThread& control );
	virtual ~loadInitData();
	void operator( )();

private:

	CrtlThread& m_control;

	bool LoadXML( TiXmlElement* pXMLData );

};

#endif /* LOADINITDATA_H_ */
