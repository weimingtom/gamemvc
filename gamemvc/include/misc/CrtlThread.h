/*
 * CrtlThread.h
 *
 *  Created on: 19-jun-2009
 *      Author: 79481180
 */

#ifndef CRTLTHREAD_H_
#define CRTLTHREAD_H_

#include <iostream>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

class CrtlThread
{

public:
	CrtlThread( void ) :
		m_mutex(), m_stopCommanded( false ), m_endThread( false ), m_error(0) {
	}

	void stop( void ) {
		boost::mutex::scoped_lock lock( m_mutex );
		m_stopCommanded = true;

	}

	bool stopWasCommanded( void ) const {
		boost::mutex::scoped_lock lock( m_mutex );
		return m_stopCommanded;
	}
	void end( void ) {
		boost::mutex::scoped_lock lock( m_mutex );
		m_endThread = true;

	}
	bool endWasCommanded( void ) const {
		boost::mutex::scoped_lock lock( m_mutex );
		return m_endThread;
	}
	void setError( int error ) {
		boost::mutex::scoped_lock lock( m_mutex );
		m_error = error;
	}
	int getError( void ) const {
		boost::mutex::scoped_lock lock( m_mutex );
		return m_error;
	}

private:

	mutable boost::mutex 	m_mutex;
	bool 					m_stopCommanded;
	bool 					m_endThread;
	int						m_error;

};

#endif /* CRTLTHREAD_H_ */
