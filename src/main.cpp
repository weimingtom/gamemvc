#include <string>
#include <iostream>

#include <SDL/SDL_framerate.h>
#include <boost/program_options.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <misc/debug.h>
#include <misc/log.h>

#include <states/introstate/CIntroState.h>
#include <states/menustate/CMenuState.h>

#include "MyGame.h"

namespace po = boost::program_options;

#ifdef DEBUG

// Con esto los mensajes en la consola.
//
// Sin esto no funciona el nvwa ....
// seguro que es el catch que hace el SDL para enviarlos
// a un fichero ...... y posiblemente sea el buffer o similar.
//
/*
#ifdef main
#undef main
#endif
*/
#endif

int main( 	int argc,
			char *argv[] ) {

	FPSmanager manager;

	try {

		init_logs();

#ifdef DEBUG

		g_log_level()->set_enabled( boost::logging::level::info );
		char* p = new char[128];

#else

		g_log_level()->set_enabled( boost::logging::level::error );

#endif

		std::string config;
		po::options_description desc( "Allowed options" );
		desc.add_options()( "help",
							"produce help message" )(	"config",
														po::value < std::string >( &config )->default_value( "game.ini" ),
														"Optionally provide a path to a file that contains configuration settings" );

		po::variables_map vm;
		po::store( 	po::parse_command_line( argc,
											argv,
											desc ),
					vm );
		po::notify( vm );

		if ( vm.count( "help" ) ) {
			std::cout << desc << std::endl;
			return 1;
		}

		// initialize the engine
		game.Init( config );

		// load the intro
		game.ChangeState( &IntroState );

		// main loop
		SDL_initFramerate( &manager );
		SDL_setFramerate(	&manager,
							25 );
		while ( game.Running() ) {

			LAPP_
<<			" ";
			LAPP_ << "Comienzo bucle --- ";
			Uint32 timeStart = SDL_GetTicks();

			game.HandleEvents();

			Uint32 timeHandleEvents = SDL_GetTicks();
			LAPP_ << "Time HandleEvents : " << timeHandleEvents - timeStart;

			game.Update();

			Uint32 timeUpdate = SDL_GetTicks();
			LAPP_ << "Time Update       : " << timeUpdate - timeHandleEvents;

			game.Draw();

			Uint32 timeDraw = SDL_GetTicks();
			LAPP_ << "Time Draw         : " << timeDraw - timeUpdate;

			LAPP_ << "Tiempo total      : " << SDL_GetTicks() - timeStart;

			SDL_framerateDelay( &manager );
			LAPP_ << "Tiempo bucle      : " << SDL_GetTicks() - timeStart;

		}

		// cleanup the engine
		game.Cleanup();

	} catch ( po::error const &e ) {

		LERR_ << e.what();
		return 1;

	} catch ( pt::ini_parser_error const &e ) {

		LERR_ << e.what();
		return 1;

	} catch ( gcn::Exception const &e ) {

		LERR_ << e.getMessage();
		return 1;

	} catch ( std::exception const &e ) {

		LERR_ << "trapped exception: " << e.what();
		return 1;

	} catch ( ... ) {

		LERR_ << "Unknown exception";
		return 1;

	}
	return 0;
}
