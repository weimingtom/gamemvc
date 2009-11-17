/*
 * log.h
 *
 *  Created on: 15/09/2009
 *      Author: 79481180
 */

#ifndef LOG_H_
#define LOG_H_

#include <boost/logging/format_fwd.hpp>
// #include <boost/logging/writer/on_dedicated_thread.hpp> // uncomment if you want to do logging on a dedicated thread
// Step 1: Optimize : use a cache string, to make formatting the message faster
BOOST_LOG_FORMAT_MSG( optimize::cache_string_one_str<> )

#ifndef BOOST_LOG_COMPILE_FAST
#include <boost/logging/format.hpp>
#include <boost/logging/writer/ts_write.hpp>
#endif

// Step 3 : Specify your logging class(es)
// typedef boost::logging::logger_format_write <boost::logging::default_, boost::logging::default_, boost::logging::writer::threading::on_dedicated_thread > logger_type;
typedef boost::logging::logger_format_write <> logger_type;
// Step 4: declare which filters and loggers you'll use
BOOST_DECLARE_LOG_FILTER(g_log_level, boost::logging::level::holder_ts )
// holds the application log level
BOOST_DECLARE_LOG(g_log_err, logger_type)
BOOST_DECLARE_LOG(g_log_app, logger_type)
BOOST_DECLARE_LOG(g_log_dbg, logger_type)

#define LDBG_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg(), g_log_level(), debug ) << "[dbg] "
#define LERR_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_err(), g_log_level(), error )
#define LAPP_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app(), g_log_level(), info ) << "[app] "

void init_logs();

#endif /* LOG_H_ */
