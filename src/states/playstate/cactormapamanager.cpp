/*
 * CActorMapaManager.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "cactormapamanager.h"

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

#include <tinyxml.h>

#include <misc/utils.h>
#include <game/GameException.h>
#include <game/EntityManager.h>
#include <game/database/CActorManager.h>
#include <game/database/CActorType.h>

#include <Lua/CLuaManager.h>

#include "playmodel.h"

#include "cactormapa.h"

CActorMapaManager::CActorMapaManager( PlayModel* pModel ) :
    m_pModel( pModel )
{

}

bool CActorMapaManager::Load( TiXmlElement* pXMLData )
{

  int x;
  int y;
  if ( !pXMLData ) return false;

  TiXmlElement *pActorMapa = NULL;
  pActorMapa = pXMLData->FirstChildElement( "actor" );
  // Loop through each type in the Actor
  while ( pActorMapa ) {

    THROW_GAME_EXCEPTION_IF( !(pActorMapa->Attribute("x")),
                             "Error x ActorMapa no definido" );
    x = atoi( pActorMapa->Attribute( "x" ) );

    THROW_GAME_EXCEPTION_IF( !(pActorMapa->Attribute("y")),
                             "Error y ActorMapa no definido" );
    y = atoi( pActorMapa->Attribute( "y" ) );

    /*
     * Creacion de los actores. Viene definida su posicion
     * en coordenadas isometricas, se han de pasar a locales
     * para realizar todos los calculos de movimientos.
     *
     *	1.- Obtener el Actor tipo.
     * 	2.- Pasar coordenadas a Local.
     *  3.- Crear el actor en lua con su caracter, situandolo en las
     *  	coordenadas locales calculadas.
     *
     *  		Harry.
     *  		Lilly.
     *		  	King.
     *  		Etc.
     *
     *  	al crearlo se crean los datos iniciales del mismo.
     *
     *  4.- A�adir el actor a la matriz del terreno en su posicion
     *  	isometrica.
     *
     */
    std::string elActor = pActorMapa->GetText();
    CActorType* elActorTipo = ActorManager.GetActorType( elActor );

    Vector2D pos = m_pModel->Map().MapToLocal < Vector2D >( gcn::Point( x,
                                                                        y ) );
    CActorMapa_ptr elActorMapa( luabind::call_function < CActorMapa* >( LuaManager.GetLua(),
                                                                        elActor.c_str(),
                                                                        m_pModel,
                                                                        pos, // Pasamos un valor esto deja memoria suelta
                                                                        elActorTipo )[luabind::adopt( luabind::result )] );

    m_ActorMapa.push_back( elActorMapa );
    EntityMgr->RegisterEntity( elActorMapa.get() );
    pActorMapa = pActorMapa->NextSiblingElement( "actor" );

  }
  return true;
}
std::vector < CActorMapa_ptr >& CActorMapaManager::_getActors()
{

  return m_ActorMapa;

}
