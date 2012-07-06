/**
 * main.cpp
 *
 * Author: Rafael Ugalde
 */
#include <cstdlib>
#include <string>
#include <iostream>

#include <guichan/exception.hpp>
#include <SDL/SDL_framerate.h>
#include <boost/exception/all.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <misc/debug.h>
#include <misc/Log.h>
#include <misc/Interface.h>

#include <states/introstate/introstate.h>

#include "mygame.h"

namespace po = boost::program_options;
namespace pt = boost::property_tree;

#ifdef DEBUG
/**!
 *
 *  Con esto los mensajes de error en la consola.
 *
 * Sin esto no funciona el nvwa ....
 * seguro que es el catch que hace el SDL para enviarlos
 * a un fichero ...... y posiblemente sea el buffer o similar.
 *
 */
#ifdef main
#undef main
#endif

#endif

int main( int argc,
          char *argv[] )
{

  try {

    FPSmanager manager;
    MyGame game;

#ifdef DEBUG

    std::cout.setf( std::ios::unitbuf ); // Quito el buffer al estar bajo debug....
    init_logs();
    g_log_filter()->set_enabled( boost::logging::level::debug );

#else

    init_logs();
    g_log_filter()->set_enabled( boost::logging::level::error );

#endif

    std::string config;
    po::options_description desc( "Allowed options" );
    desc.add_options()( "help",
                        "produce help message" )( "config",
                                                  po::value < std::string >( &config )->default_value( "game.ini" ),
                                                  "Optionally provide a path to a file that contains configuration settings" );

    po::variables_map vm;
    po::store( po::parse_command_line( argc,
                                       argv,
                                       desc ),
               vm );
    po::notify( vm );

    if ( vm.count( "help" ) ) {
      std::cout << desc << std::endl;
      return EXIT_SUCCESS;
    }

    // initialize the engine
    game.Init( config );

    // load the intro
    game.ChangeState( &introstate );

    // main loop
    SDL_initFramerate( &manager );
    SDL_setFramerate( &manager,
                      25 );
    while ( game.Running() ) {

      game.HandleEvents();
      game.Update();
      game.Draw();
      game.interface().flip();
      SDL_framerateDelay( &manager );

    }
    // cleanup the engine
    game.Cleanup();

  } catch ( po::error const &e ) {

    LERR_( e.what() );
    return EXIT_FAILURE;

  } catch ( pt::ini_parser_error const &e ) {

    LERR_( e.what() );
    return EXIT_FAILURE;

  } catch ( gcn::Exception const &e ) {

    LERR_( e.getMessage() );
    return EXIT_FAILURE;

  } catch ( boost::exception const &e ) {

    LERR_( boost::diagnostic_information( e ) );
    return EXIT_FAILURE;

  } catch ( ... ) {

    LERR_( "Unhandled exception!" );
    LERR_( boost::current_exception_diagnostic_information() );
    return EXIT_FAILURE;

  }
  return EXIT_SUCCESS;
}
