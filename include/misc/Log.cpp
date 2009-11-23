/*
 * Log.cpp
 *
 *  Created on: 19/11/2009
 *      Author: uberiain
 */

// my_app_log.cpp - DEFINE your loggers & filters here
#include "Log.h"
// #include <boost/logging/format/named_write.hpp>
#include <boost/logging/format_ts.hpp>
#include <boost/logging/writer/ts_write.hpp>

BOOST_DEFINE_LOG_FILTER(g_l_level, filter_type )
BOOST_DEFINE_LOG(g_l, logger_type)

void init_logs() {

	g_l()->writer().add_destination(bl::destination::cout());
	g_l()->writer().add_formatter(bl::formatter::idx(), "[%] ");
	g_l()->writer().add_formatter(bl::formatter::time("$hh:$mm.$ss "));
	g_l()->writer().add_formatter(bl::formatter::append_newline());
	g_l()->turn_cache_off();
	g_l()->mark_as_initialized();

}

void use_logger() {
	g_l_level()->set_enabled(bl::level::info);
	int i = 1;
	L_(debug)
<<	"this is a simple message " << i;
	std::string hello = "hello";
	L_(info) << hello << " world";
}
