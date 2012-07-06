/**
 *
 * IntroModel.h
 *
 *  Created on: 27-mar-2009
 *      Author: Rafael Ugalde Beriain
 *
 *      Definición del Model que ha de tratar la introducción al juego.
 *
 */

#ifndef INTROMODEL_H_
#define INTROMODEL_H_

#include <boost/thread.hpp>

#include <mvc/Model.h>
#include <misc/Interface.h>

class MyGame;
namespace gcn {

  class Gui;

}
class TiXmlElement;

/**
 *
 *  Parte de la estructura  MVC de la introduccion, se encarga de cargar todos los datos
 *  iniciales del juego. Lo hace mediante una thread que se ejecuta en paralelo con la
 *  visualizacion en pantalla de un contador que se va decrementando. Este contador puede ser
 *  sustituido en su momento por un video, una animacion o cualquier otra cosa.
 *  Realmente es el uso de thread para la carga de los datos lo que he experimentado en este
 *  estado.
 *
 *  Uso:
 *  Se crea en el Init del estado Intro pasando como parametro la referencia a la clase donde
 *  tenemos los parametros base del juego.
 *
 *  \code
 *  model_ = new IntroModel(*game_);
 *  \endcode
 *
 */
class IntroModel: public Model
{
  public:

    enum EndTypes
    {
      CONTINUE = -1,
      QUIT,
      MENU

    };
    /**
     * Creacion de la parte Model de la introducción, se crea al principio como parte de la
     * estructura MVC.
     *
     * El parametro de entrada es la referencia a la variable que contiene los parametros
     * globales del juego. Este objeto los referencia.
     *
     * @param game  Referencia a la variable con los datos globales del juego.
     * @return      Variable creada.
     */
    IntroModel( MyGame& game );
    /**
     * Destruccion de la parte Model de la introduccion.
     * @return
     */
    virtual ~IntroModel();
    /**
     * Actualizacion de los datos del model. Es llamada por el IntroState en cada bucle
     * del juego.
     */
    void Update();

    // Set and Get de las variables de la clase.

    void endtype( const IntroModel::EndTypes& type );
    IntroModel::EndTypes endtype() const;
    void final();
    const int& alpha() const;
    const Interface::ScreenResolutionType& resolution() const;
    gcn::Gui& screen() const;

  private:

    //! Referencia datos globales del juego.
    MyGame& game_;
    //! Contador para representacion en pantalla.
    int alpha_;
    //! Nos indica que nos han pedido terminar antes de terminar el contador
    bool final_;
    //! Tipo de finalizacion requerida.
    IntroModel::EndTypes endtype_;
    //! Resolucion actual de la pantalla.
    Interface::ScreenResolutionType resolution_;

    //! Tarea a ejecutar.
    boost::packaged_task < int > pt_;
    //! Resultado final de la tarea.
    boost::unique_future < int > fi_;
    //! Tarea como tal.
    boost::thread thr_;

    /**
     * Thread donde se cargan los datos globales del juego. Se crea este thread en la propia
     * creacion de la clase IntroModel
     * @return Resultado de la ejecucion del thread.
     */
    int Run();
    /**
     * Cargar los distintos elementos del juego desde el fichero xml.
     *
     * @param pXMLData
     * @return  TRUE = resultado correcto de la carga del fichero XML.
     */
    bool LoadXML( TiXmlElement* pXMLData );

};

#endif /* INTROMODEL_H_ */
