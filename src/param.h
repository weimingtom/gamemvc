/**
 * Param.h
 *
 *  Created on: 25/01/2010
 *      Author: uberiain
 */
#ifndef PARAM_H_
#define PARAM_H_

#include <string>

class Param
{
  public:
    Param( const std::string& config );
    virtual ~Param();

    struct screen
    {
        //! Resolucion pantalla.
        std::string resolution;
        //! Fullscreen.
        bool full;
        //! Icono del programa.
        std::string icon;
        //! Font por defecto guichan.
        std::string font;

    } screen;
    //! Fichero datos iniciales del game.
    std::string gamedata;
    //! Fichero carga inicial Lua.
    std::string lua;
};
#endif /* PARAM_H_ */
