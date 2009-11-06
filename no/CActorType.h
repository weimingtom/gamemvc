/*
 * CActorType.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CACTORTYPE_H_
#define CACTORTYPE_H_


#include <map>
#include <string>
using namespace std;

#include <lua.hpp>
#include <luabind/luabind.hpp>

class CPersonality;
class TiXmlElement;

class CActorType {
public:

	~CActorType();

	bool 			Load(TiXmlElement* pXMLData);
	string 			GetNameActorType();
	CPersonality*	GetPersonality(string personality);

private:

	string					m_Name;			//!
	map< string, CPersonality* > m_mPersonality;

};

#endif /* CACTORTYPE_H_ */
