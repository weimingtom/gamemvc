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
#include <boost/shared_ptr.hpp>
#include <lua.hpp>
#include <luabind/luabind.hpp>

class CPersonality;
class TiXmlElement;

class CActorType {
public:

	bool 			Load(TiXmlElement* pXMLData);
	bool 			PersonalityExist( const std::string& personality) const;
	CPersonality& GetPersonality(const std::string& personality);

private:

	typedef boost::shared_ptr < CPersonality > CPersonality_ptr;
	typedef std::map<std::string , CPersonality_ptr > CPersonality_map;

	CPersonality_map m_mPersonality;

};

#endif /* CACTORTYPE_H_ */
