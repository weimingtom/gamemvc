/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "Exception.hpp"

Exception::Exception( 	const char* fileName,
						int lineNo,
						const char* message1,
						const char* message2,
						Reason reasonNo ) :
	std::exception(), m_fileName( fileName ), m_lineNo( lineNo ),
			m_message1( message1 ), m_message2( message2 ),
			m_reasonNo( reasonNo ) {
}
