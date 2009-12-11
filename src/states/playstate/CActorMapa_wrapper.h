/*
 * Actor_wrapper.h
 *
 *  Created on: 20-jul-2008
 *      Author: Administrador
 */

#ifndef CACTORMAPA_WRAPPER_H_
#define CACTORMAPA_WRAPPER_H_
/*!
 * @brief  Wrapper de la class Actor
 *
 * Utilizada para definir la clase en Lua y acceder a sus metodos
 * desde C++ y desde Lua a los metodos de C++
 *
 */
#include <iostream>

struct ActorMapa_wrapper: CActorMapa, wrap_base
{

	ActorMapa_wrapper( 	PlayModel* elGameWorld,
						Vector2D laPosicion,
						CActorType* elActorTipo ) :
		CActorMapa( elGameWorld, laPosicion, elActorTipo ) {
//		std::cout << "[C++ActorMapa_wrapper] constructor" << std::endl;
	}
	void UpdateFrame( long iElapsedTicks ) {
		call< void > ( "UpdateFrame", iElapsedTicks );
	}
	static void default_UpdateFrame(CActorMapa* ptr, long iElapsedTicks ) {

		ptr->CActorMapa::UpdateFrame( iElapsedTicks );

		return;

	}
	bool HandleMessage( const Telegram& msg ){

		return call<bool>("HandleMessage", msg);

	}
	static bool default_HandleMessage(CActorMapa* ptr, const Telegram& msg){

		return ptr->CActorMapa::HandleMessage( msg );

	}
	virtual ~ActorMapa_wrapper() {
//		std::cout << "[C++ActorMapa_wrapper] destructor" << std::endl;
	}
};

#endif /* CACTORMAPA_WRAPPER_H_ */
