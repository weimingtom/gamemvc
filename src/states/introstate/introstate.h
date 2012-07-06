/**
 *
 * IntroState.h
 *
 *  Created on: 27-mar-2009
 *      Author: Rafael Ugalde Beriain
 *
 *      Definici�n del estado Intro.
 *
 */
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <game/gamestate.hpp>
#include <misc/singleton.hpp>

#define introstate Singleton < IntroState >::Instance()

class IntroModel;
class IntroView;

class MyGame;
class GameEngine;
/**
 * Estado inicial de la aplicacion. Se define como un singleton ya que cada estado
 * ha de ser unico dentro de toda la aplicacion.
 *
 * Se ejecuta antes del comienzo del bucle del juego. La forma de ejecucion es la siguiente:
 * \code
 * game.ChangeState( &introstate );
 * \endcode
 */
class IntroState: public GameState
{
  public:

    virtual ~IntroState();

    void Init( GameEngine* game );
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents();
    void Update();
    void Draw();

  private:

    //! Contiene el estado del juego y los datos globales.
    MyGame* game_;
    //! Parte MODEL de la estructura MVC
    IntroModel* model_;
    //! Parte VIEW de la estructura MVC
    IntroView* view_;

};

#endif

