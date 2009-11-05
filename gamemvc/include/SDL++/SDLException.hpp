/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef SDL_EXCEPTION_HPP
#define SDL_EXCEPTION_HPP

#include <SDL++/Exception.hpp>

/**
 * @brief Sdl exception class for IsoHexEngine.
 */
class SdlException: public Exception {
public:
	explicit SdlException(const char* fileName, int lineNo,
			const char* message1);
};

#define THROW_SDL_EXCEPTION_IF(condition, message1) \
    if (condition) \
    { \
        throw SdlException( \
                __FILE__, \
                __LINE__, \
                message1); \
    }

#endif // SDL_EXCEPTION_HPP
