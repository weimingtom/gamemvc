/*
 * GameException.cpp
 *
 *  Created on: 12-ago-2008
 *      Author: 79481180
 */

#include "GameException.h"

GameException::GameException( char * razon )
{
  stackTrace = razon;
}

/**
 * Retorna la descripcin de la excepcin ocurrida.
 * @return La descripcin de la excepcin ocurrida.
 */
const char* GameException::what() const throw ()
{
  return stackTrace;
}

