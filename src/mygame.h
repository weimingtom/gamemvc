/*
 * MyGame.h
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */

#ifndef MYGAME_H_
#define MYGAME_H_

#include <string>

#include <boost/scoped_ptr.hpp>

#include <game/GameEngine.h>

class Interface;
class Param;

class MyGame: public GameEngine
{
  public:

    MyGame();
    virtual ~MyGame();

    void Init( const std::string& config );
    void Cleanup();

    Interface& interface() const;
    Param& param() const;

  private:

    boost::scoped_ptr < Interface > interface_;
    boost::scoped_ptr < Param > param_;

    /*
     * Procedimientos privados.
     */
    void InitParam( const std::string& config );
    void InitInterface();
    void InitLua();

};

#endif /* MYGAME_H_ */
