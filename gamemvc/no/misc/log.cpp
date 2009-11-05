/*
 * log.cpp
 *
 *  Created on: 15/09/2009
 *      Author: 79481180
 */
#include "log.h"

#include <boost/logging/format_ts.hpp>
#include <boost/logging/format/formatter/tags.hpp>
#include <boost/logging/format/formatter/named_spacer.hpp>

using namespace boost::logging;

BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder_ts )
// holds the application log level
BOOST_DEFINE_LOG(g_log_err, logger_type)
BOOST_DEFINE_LOG(g_log_app, logger_type)
BOOST_DEFINE_LOG(g_log_dbg, logger_type)

void init_logs() {

	// Log app
	g_log_app()->writer().add_formatter( 	formatter::idx(),
											"[%] " );
	g_log_app()->writer().add_formatter( formatter::time("$hh:$mm.$ss ") );
	g_log_app()->writer().add_formatter( formatter::append_newline_if_needed() );
	g_log_app()->writer().add_destination( destination::cout() );

	// Log err
	g_log_err()->writer().add_formatter( 	formatter::idx(),
											"[%] " );
	g_log_err()->writer().add_formatter( formatter::time("$hh:$mm.$ss ") );

	g_log_err()->writer().add_formatter( formatter::append_newline_if_needed() );
	g_log_err()->writer().add_destination( destination::cout() );
//	g_log_err()->writer().add_destination( destination::cerr() );

	// Log dbg
	g_log_dbg()->writer().add_formatter( 	formatter::idx(),
											"[%] " );
	g_log_dbg()->writer().add_formatter( formatter::time("$hh:$mm.$ss ") );

	g_log_dbg()->writer().add_formatter( formatter::append_newline_if_needed() );
//	g_log_dbg()->writer().add_destination( destination::dbg_window() );
	g_log_dbg()->writer().add_destination( destination::cout() );

	g_log_app()->mark_as_initialized();
	g_log_err()->mark_as_initialized();
	g_log_dbg()->mark_as_initialized();

}
