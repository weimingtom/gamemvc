/*
 * Log.cpp
 *
 *  Created on: 19/11/2009
 *      Author: uberiain
 */

// log.cpp - DEFINE your loggers & filters here
#include "Log.h"

using namespace boost::logging;

BOOST_DEFINE_LOG_FILTER( g_log_filter,
                         level::holder )
BOOST_DEFINE_LOG( g_log_err,
                  logger_type )
BOOST_DEFINE_LOG( g_log_app,
                  logger_type )
BOOST_DEFINE_LOG( g_log_dbg,
                  logger_type )

void init_logs()
{

  // Err log
  g_log_err()->writer().add_formatter( formatter::idx(),
                                       "[%] " );
  g_log_err()->writer().add_formatter( formatter::time( "$hh:$mm.$ss " ) );
  g_log_err()->writer().add_formatter( formatter::append_newline() );
  g_log_err()->writer().add_destination( destination::cerr() );
  g_log_err()->turn_cache_off();

  // App log
  g_log_app()->writer().add_formatter( formatter::time( "$hh:$mm.$ss " ) );
  g_log_app()->writer().add_formatter( formatter::append_newline() );
  g_log_app()->writer().add_destination( destination::cout() );
  g_log_app()->turn_cache_off();

  // Debug log
  g_log_dbg()->writer().add_formatter( formatter::time( "$hh:$mm.$ss " ) );
  g_log_dbg()->writer().add_formatter( formatter::append_newline() );
  g_log_dbg()->writer().add_destination( destination::dbg_window() );
  g_log_dbg()->writer().add_destination( destination::cout() );
  g_log_dbg()->turn_cache_off();

  g_log_app()->mark_as_initialized();
  g_log_err()->mark_as_initialized();
  g_log_dbg()->mark_as_initialized();

}
