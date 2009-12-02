/*
 * Log.cpp
 *
 *  Created on: 19/11/2009
 *      Author: uberiain
 */

// my_app_log.cpp - DEFINE your loggers & filters here
#include "Log.h"
#include <boost/logging/format/named_write.hpp>

BOOST_DEFINE_LOG_FILTER(g_l_level, filter_type )
BOOST_DEFINE_LOG(g_l, logger_type)

void init_logs() {
    // formatting    : time [idx] message \n
    // destinations  : console, file "out.txt" and debug window
    g_l()->writer().write("%time%($hh:$mm.$ss.$mili) [%idx%] |\n", "cout");
    g_l()->mark_as_initialized();
}
