#include <string>
#include <iostream>

#include <SDL/SDL_framerate.h>
#include <boost/program_options.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <misc/debug.h>

#include <states/introstate/CIntroState.h>
#include <states/menustate/CMenuState.h>

#include "MyGame.h"

namespace po = boost::program_options;
namespace pt = boost::property_tree;

int main( 	int argc,
			char *argv[] ) {

	FPSmanager manager;

	try {

		//		init_logs();

#ifdef DEBUG

		extern FILE* new_output_fp;
		new_output_fp = fopen(	"nvwa.lst",
								"w" );
		char* p = new char[128];
		if ( stderr == new_output_fp ) {
			fprintf( 	new_output_fp,
						"Esto es una salida en stderr\n" );
		} else if ( stdout == new_output_fp ) {
			fprintf( 	new_output_fp,
						"Esto esta en stdout\n" );
		} else {
			fprintf( 	new_output_fp,
						"Esto no esta en stderr\n" );
		}
		//		g_log_level()->set_enabled( boost::logging::level::info );

#else
		//		g_log_level()->set_enabled( boost::logging::level::error );
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
							20 );
		while ( game.Running() ) {

			//			LAPP_
			//			LAPP_ << "Comienzo bucle --- ";
			Uint32 timeStart = SDL_GetTicks();

			game.HandleEvents();

			Uint32 timeHandleEvents = SDL_GetTicks();
			//			LAPP_ << "Time HandleEvents : " << timeHandleEvents - timeStart;

			game.Update();

			Uint32 timeUpdate = SDL_GetTicks();
			//			LAPP_ << "Time Update       : " << timeUpdate - timeHandleEvents;

			game.Draw();

			Uint32 timeDraw = SDL_GetTicks();
			//			LAPP_ << "Time Draw         : " << timeDraw - timeUpdate;

			//			LAPP_ << "Tiempo total      : " << SDL_GetTicks() - timeStart;

			SDL_framerateDelay( &manager );
			//			LAPP_ << "Tiempo bucle      : " << SDL_GetTicks() - timeStart;

		}

		// cleanup the engine
		game.Cleanup();

#ifdef DEBUG
		fprintf( 	new_output_fp,
					"Final del bucle game\n" );
#endif

	} catch ( po::error const &e ) {

		std::cerr << e.what() << std::endl;
		return 1;

	} catch ( pt::ini_parser_error const &e ) {

		std::cerr << e.what() << std::endl;
		return 1;

	} catch ( gcn::Exception const &e ) {

		std::cerr << e.getMessage() << std::endl;
		return 1;

	} catch ( std::exception const &e ) {

		std::cerr << "trapped exception: " << e.what() << std::endl;
		return 1;

	} catch ( ... ) {

		std::cerr << "Unknown exception" << std::endl;
		return 1;

	}
#ifdef DEBUG
	fprintf( 	new_output_fp,
				"Final del programa\n" );
#endif
	return 0;
}
