/*
 * Param.cpp
 *
 *  Created on: 25/01/2010
 *      Author: uberiain
 */

#include "Param.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace pt = boost::property_tree;

Param::Param(const std::string& config) {

    pt::ptree pt;
    pt::read_ini( config,
                  pt );

    screen.resolution = pt.get < std::string > ( "screen.resolution",
                                                       "SMALL" );

    screen.full = pt.get( "screen.fullscreen",
                                false );
    screen.icon = pt.get < std::string > ( "screen.icon" );
    screen.font = pt.get < std::string > ( "screen.font" );
    gamedata = pt.get < std::string > ( "game.gamedata" );
    lua = pt.get < std::string > ( "game.lua" );
}

Param::~Param() {
}
