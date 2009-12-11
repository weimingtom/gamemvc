/*
 * CActorMapaManager.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "CActorMapaManager.h"

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

#include <tinyxml.h>

#include <misc/utils.h>
#include <game/GameException.h>
#include <game/EntityManager.h>
#include <game/database/CActorManager.h>
#include <game/database/CActorType.h>

#include <Lua/CLuaManager.h>

#include "PlayModel.h"

#include "CActorMapa.h"

CActorMapaManager::CActorMapaManager( PlayModel* pModel ) :
	m_pModel( pModel ) {

}

CActorMapaManager::~CActorMapaManager() {

	DeleteSTLContainer( m_ActorMapa );

}

bool CActorMapaManager::Load( TiXmlElement* pXMLData ) {

	int x;
	int y;
	if ( !pXMLData ) return false;

	TiXmlElement *pActorMapa = NULL;
	pActorMapa = pXMLData->FirstChildElement( "actor" );
	// Loop through each type in the Actor
	while ( pActorMapa ) {

		THROW_GAME_EXCEPTION_IF(!(pActorMapa->Attribute("x")),"Error x ActorMapa no definido");
		x = atoi( pActorMapa->Attribute( "x" ) );

		THROW_GAME_EXCEPTION_IF(!(pActorMapa->Attribute("y")),"Error y ActorMapa no definido");
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
		 *  4.- Añadir el actor a la matriz del terreno en su posicion
		 *  	isometrica.
		 *
		 */
		string elActor = pActorMapa->GetText();
		CActorType* elActorTipo = ActorManager.GetActorType( elActor );
		/*
		Vector2D pos = m_pModel->MapToLocal( 	x,
												y );
		CActorMapa* elActorMapa =
				call_function < CActorMapa* > ( LuaManager.GetLua(),
												elActor.c_str(),
												m_pModel,
												pos, // Pasamos un valor esto deja memoria suelta
												elActorTipo )[adopt( result )];
		*/
//		m_ActorMapa.push_back( elActorMapa );
//		EntityMgr->RegisterEntity( elActorMapa );
		pActorMapa = pActorMapa->NextSiblingElement( "actor" );

	}
	return true;
}
vector < CActorMapa* >& CActorMapaManager::_getActors() {

	return m_ActorMapa;

}

