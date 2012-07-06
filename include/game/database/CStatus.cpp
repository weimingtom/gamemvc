/*
 * CStatus.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CStatus.h"

#include <tinyxml.h>
#include <game/GameException.h>

#include "CDir.h"

bool CStatus::Load( TiXmlElement* pXMLData )
{

  if ( !pXMLData ) return false;

  THROW_GAME_EXCEPTION_IF( !(pXMLData->Attribute("frames")),
                           "Error frames Actor no definido" );
  m_iFrames = atoi( pXMLData->Attribute( "frames" ) );

  TiXmlElement *pDir = NULL;
  pDir = pXMLData->FirstChildElement( "dir" );
  while ( pDir ) {

    THROW_GAME_EXCEPTION_IF( !pDir->Attribute("name"),
                             "Error name Actor no definido" );
    std::string name( pDir->Attribute( "name" ) );
    CDir_ptr laDir( new CDir() );

    if ( laDir->Load( pDir ) == false ) return false;

    // Añadir las diferentes direcciones al estado.
    m_mDir[name] = laDir;
    pDir = pDir->NextSiblingElement( "dir" );

  }

  return true;
}
bool CStatus::DirExist( const std::string& laDir ) const
{
  return m_mDir.find( laDir ) != m_mDir.end();
}
CDir* CStatus::GetDir( const std::string& laDir )
{

  return m_mDir[laDir].get();

}
int CStatus::GetFrames() const
{
  return m_iFrames;
}
