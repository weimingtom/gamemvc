/*
 * MyGame.h
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */

#ifndef MYGAME_H_
#define MYGAME_H_

#include <string>
#include <boost/utility.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <game/CGameEngine.h>

namespace pt = boost::property_tree;
class Interface;

class MyGame: public CGameEngine
{
public:

    MyGame();
    virtual ~MyGame();

    void Init( const std::string& config );
    void Cleanup();

    Interface& interface() const;

private:

    std::auto_ptr < Interface > m_interface_;
    pt::ptree pt;

    /*
     * Procedimientos privados.
     */
    void InitParam( const std::string& config );
    void InitInterface();
    void InitLua();

};

#endif /* MYGAME_H_ */
