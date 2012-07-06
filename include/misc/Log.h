/*
 * Log.h
 *
 *  Created on: 19/11/2009
 *      Author: uberiain
 */
// log.h - DECLARE your loggers & filters here
#ifndef LOG_H_
#define LOG_H_

#include <boost/logging/format_fwd.hpp>

BOOST_LOG_FORMAT_MSG( optimize::cache_string_one_str<> )

#include <boost/logging/format.hpp>

typedef boost::logging::logger_format_write < > logger_type;

BOOST_DECLARE_LOG_FILTER( g_log_filter,
                          boost::logging::level::holder )
BOOST_DECLARE_LOG( g_log_err,
                   logger_type )
BOOST_DECLARE_LOG( g_log_app,
                   logger_type )
BOOST_DECLARE_LOG( g_log_dbg,
                   logger_type )

#define LDBG_(msg) BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg(), g_log_filter(), debug ) << "[dbg] " << msg
#define LERR_(msg) BOOST_LOG_USE_LOG_IF_LEVEL(g_log_err(), g_log_filter(), error ) << msg
#define LAPP_(msg) BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app(), g_log_filter(), info ) << "[app] " << msg

void init_logs();

#endif /* LOG_H_ */
