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
#include <boost/shared_ptr.hpp>

class TiXmlElement;
class CDir;

class CStatus
{
public:

	bool Load( TiXmlElement* pXMLData );
	bool DirExist( const std::string& laDir) const;
	CDir* GetDir( const std::string& laDir );
	int GetFrames() const;

private:

	int m_iFrames; //! Contador de cambio de frames.

	typedef boost::shared_ptr < CDir > CDir_ptr;
	typedef std::map<std::string , CDir_ptr > CDir_map;
	CDir_map m_mDir;
};

#endif /* CSTATUS_H_ */
