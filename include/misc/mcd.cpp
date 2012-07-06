/*
 * mcd.cpp
 *
 *  Created on: 27/01/2010
 *      Author: 79481180
 */

#include "mcd.h"

int mcd( int a,
         int b )
{

  int x;
  int y = 1;
  int i = 2;
  int z;

  if ( a < b ) {
    x = a;
    z = b;
  } else {
    x = b;
    z = a;
  }

  do {
    if ( x % i == 0 && z % i == 0 ) {
      y = y * i;
      x = x / i;
      z = z / i;
      i = 2;
    } else
      i++;

  } while ( i <= x );
  return y;
}
