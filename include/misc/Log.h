/*
 * Log.h
 *
 *  Created on: 19/11/2009
 *      Author: uberiain
 */
// my_app_log.h - DECLARE your loggers & filters here
#ifndef LOG_H_
#define LOG_H_

#define BOOST_LOG_TSS_USE_BOOST
#include <boost/logging/format_fwd.hpp>
#include <boost/logging/writer/on_dedicated_thread.hpp>

#ifndef BOOST_LOG_COMPILE_FAST
#include <boost/logging/format.hpp>
#include <boost/logging/writer/ts_write.hpp>
#endif

namespace bl = boost::logging;

// Step 3 : Specify your logging class(es)
//default_, default_, writer::threading::on_dedicated_thread
typedef bl::logger_format_write < bl::default_, bl::default_,
		bl::writer::threading::on_dedicated_thread > logger_type;
typedef bl::level::holder filter_type;
BOOST_DECLARE_LOG_FILTER(g_l_level, filter_type)
BOOST_DECLARE_LOG(g_l, logger_type)

#define L_(lvl) BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_level(), lvl )
#define Q_(lvl,out) BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_level(), lvl ) << (out);
// initialize thy logs..
void init_logs();

#endif /* LOG_H_ */
