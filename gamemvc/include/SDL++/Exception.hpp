/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

/**
 * @brief General exception class for IsoHexEngine.
 */
class Exception: public std::exception {
public:
	enum Reason {
		UNKNOWN_REASON, SDL_REASON
	};

	explicit Exception(const char* fileName, int lineNo, const char* message1,
			const char* message2, Reason reasonNo);

	virtual ~Exception() throw () {
	}

	const std::string m_fileName;
	const int m_lineNo;
	const std::string m_message1;
	const std::string m_message2;
	const Reason m_reasonNo;
};

#define THROW_EXCEPTION_IF(condition, message1, message2, reason) \
    if (condition) \
    { \
        throw isohexengine::core::Exception( \
                __FILE__, \
                __LINE__, \
                message1, \
                message2, \
                reason); \
    }

#endif // EXCEPTION_HPP
