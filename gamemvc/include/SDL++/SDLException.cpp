/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "SdlException.hpp"

#include <SDL/SDL.h>

SdlException::SdlException(
    const char* fileName,
    int lineNo,
    const char* message1)
: Exception(fileName, lineNo, message1, SDL_GetError(), SDL_REASON)
{
}
