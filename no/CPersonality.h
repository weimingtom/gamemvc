/*
 * CPersonality.h
 *
 *  Created on: 15-dic-2008
 *      Author: 79481180
 */

#ifndef CPERSONALITY_H_
#define CPERSONALITY_H_

#include <map>
#include <string>
#include <tinyxml.h>

class CStatus;

class CPersonality
{
public:

	virtual ~CPersonality();

	bool Load( TiXmlElement* pXMLData );
	string GetNamePersonality();
	CStatus* GetStatus( const std::string& status );

private:

	std::string m_Name;
	map < std::string, CStatus* > m_mStatus;

};

#endif /* CPERSONALITY_H_ */
