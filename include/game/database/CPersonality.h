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
#include <boost/shared_ptr.hpp>

class CStatus;
class TiXmlElement;

class CPersonality
{
public:

	bool Load( TiXmlElement* pXMLData );
	bool StatusExist( const std::string& status) const;
	CStatus& GetStatus( const std::string& status );

private:

	typedef boost::shared_ptr < CStatus > CStatus_ptr;
	typedef std::map<std::string , CStatus_ptr > CActorType_map;

	CActorType_map m_mStatus;

};

#endif /* CPERSONALITY_H_ */
