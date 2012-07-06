/*
 * GameException.h
 *
 *  Created on: 12-ago-2008
 *      Author: 79481180
 */

#ifndef GAMEEXCEPTION_H_
#define GAMEEXCEPTION_H_

#include <sstream>
#include <iostream>
#include <exception>

class GameException : public std::exception
{

  private:
    char* stackTrace;

  public:
    GameException( char* );
    virtual const char* what() const throw ();

};
/*
 #define throwGameException(e) {\
	stringstream msg; \
	msg << e << " en " << __FILE__ << " linea " << __LINE__ << ends; \
	throw GameException((char*) msg.str().c_str()); \
}
 */
#define THROW_GAME_EXCEPTION_IF(condition, e) \
    if (condition) \
    { \
    	std::stringstream msg; \
    	msg << e << " en " << __FILE__ << " linea " << __LINE__ << std::ends; \
        throw GameException( \
        		(char*) msg.str().c_str()); \
    }
#endif /* GAMEEXCEPTION_H_ */
