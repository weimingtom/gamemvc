#include <cstdlib>
#include <string>
#include <iostream>

#include <SDL/SDL_framerate.h>
#include <boost/program_options.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <misc/debug.h>
#include <misc/Log.h>

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

#ifdef main
#undef main
#endif

#endif

int main( 	int argc,
			char *argv[] ) {

	FPSmanager manager;

	try {

		init_logs();

#ifdef DEBUG

		//		char* q = new char[128]; // Solo esta para forzar el error en NVWA

		g_l_level()->set_enabled( bl::level::info );
		std::cout.setf( std::ios::unitbuf ); // Quito el buffer al estar bajo debug....

#else

		g_l_level()->set_enabled(bl::level::error);

#endif

		//		Q_(debug,"Hola como esta" << "y mas cosas" << 1) //!TODO No funciona

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
			return EXIT_SUCCESS;
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

			L_(debug)
<<			"Comienzo bucle";
			Uint32 timeStart = SDL_GetTicks();

			game.HandleEvents();

			Uint32 timeHandleEvents = SDL_GetTicks();
			L_(debug) << "Time HandleEvents : " << timeHandleEvents - timeStart;
			game.Update();

			Uint32 timeUpdate = SDL_GetTicks();
			L_(debug) << "Time Update       : " << timeUpdate - timeHandleEvents;
			game.Draw();

			Uint32 timeDraw = SDL_GetTicks();
			L_(debug)<< "Time Draw         : " << timeDraw - timeUpdate;

			L_(debug) << "Tiempo total      : " << SDL_GetTicks() - timeStart;

			SDL_framerateDelay(&manager);
			L_(debug) << "Tiempo bucle      : " << SDL_GetTicks() - timeStart;

		}

		// cleanup the engine
		game.Cleanup();

	} catch (po::error const &e) {

		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;

	} catch (pt::ini_parser_error const &e) {

		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;

	} catch (gcn::Exception const &e) {

		std::cerr << e.getMessage() << std::endl;
		return EXIT_FAILURE;

	} catch (std::exception const &e) {

		std::cerr << "trapped exception: " << e.what() << std::endl;
		return EXIT_FAILURE;

	} catch (...) {

		std::cerr << "Unknown exception" << std::endl;
		return EXIT_FAILURE;

	}
	return EXIT_SUCCESS;
}
