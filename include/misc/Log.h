/*
 * Log.h
 *
 *  Created on: 19/11/2009
 *      Author: uberiain
 */
// my_app_log.h - DECLARE your loggers & filters here
#ifndef LOG_H_
#define LOG_H_

#include <boost/logging/writer/on_dedicated_thread.hpp>
#include <boost/logging/format/named_write_fwd.hpp>

namespace bl = boost::logging;
typedef bl::named_logger<>::type logger_type;
typedef bl::level::holder filter_type;

BOOST_DECLARE_LOG_FILTER(g_l_level, filter_type)
BOOST_DECLARE_LOG(g_l, logger_type)

#define L_(lvl) BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_level(), lvl )

// initialize thy logs..
void init_logs();

#endif /* LOG_H_ */
