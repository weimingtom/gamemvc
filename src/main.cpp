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

int main(int argc, char *argv[]) {

	FPSmanager manager;

	try {

#ifdef DEBUG

//		new_output_fp = fopen("stderr-NVWA.txt","w");
		char* p = new char[128];

#else

#endif

		std::string config;
		po::options_description desc("Allowed options");
		desc.add_options()("help", "produce help message")("config", po::value<
				std::string>(&config)->default_value("game.ini"),
				"Optionally provide a path to a file that contains configuration settings");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}

		// initialize the engine
		game.Init(config);

		// load the intro
		game.ChangeState(&IntroState);

		// main loop
		SDL_initFramerate(&manager);
		SDL_setFramerate(&manager, 25);
		while (game.Running()) {

			std::cout << "Comienzo bucle --- " << std::endl;
			Uint32 timeStart = SDL_GetTicks();

			game.HandleEvents();

			Uint32 timeHandleEvents = SDL_GetTicks();
			std::cout << "Time HandleEvents : " << timeHandleEvents - timeStart
					<< std::endl;

			game.Update();

			Uint32 timeUpdate = SDL_GetTicks();
			std::cout << "Time Update       : " << timeUpdate
					- timeHandleEvents << std::endl;

			game.Draw();

			Uint32 timeDraw = SDL_GetTicks();
			std::cout << "Time Draw         : " << timeDraw - timeUpdate
					<< std::endl;

			std::cout << "Tiempo total      : " << SDL_GetTicks() - timeStart
					<< std::endl;

			SDL_framerateDelay(&manager);
			std::cout << "Tiempo bucle      : " << SDL_GetTicks() - timeStart
					<< std::endl;

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
