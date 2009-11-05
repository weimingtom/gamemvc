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
using namespace std;
#include <tinyxml.h>

class CStatus;

class CPersonality
{
public:

	virtual ~CPersonality();

	bool 		Load(TiXmlElement* pXMLData);
	string		GetNamePersonality();
	CStatus*	GetStatus(string status);

private:

	string		m_Name;
	map<string,CStatus*> m_mStatus;

};

#endif /* CPERSONALITY_H_ */
