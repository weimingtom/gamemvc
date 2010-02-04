/*
 * main.cpp
 *
 *  Created on: 22/12/2009
 *      Author: 79481180
 */

#include <guichan.hpp>
#include <boost/exception.hpp>

#include "Game.h"

int main( int argc,
          char **argv ) {

    std::cout.setf( std::ios::unitbuf );
    try {

        game.Init();
        game.run();
        game.End();

        return EXIT_SUCCESS;

    } catch ( gcn::Exception e ) {

        std::cout << e.getMessage() << std::endl;
        return EXIT_FAILURE;

    } catch ( std::exception e ) {

        std::cout << "Std exception: " << e.what() << std::endl;
        return EXIT_FAILURE;

    } catch ( ... ) {

        std::cerr << "Unhandled exception!" << std::endl
                << boost::current_exception_diagnostic_information();
        return EXIT_FAILURE;

    }
}

