/*
 * debug.h
 *
 *  Created on: 05/11/2009
 *      Author: 79481180
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#if defined(_DEBUG) && !defined(DEBUG)

#define DEBUG

#endif /* _DEBUG */

#ifdef DEBUG
#include <debug_new.h>
#endif

#endif /* DEBUG_H_ */
