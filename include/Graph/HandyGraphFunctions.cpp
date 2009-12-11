#include "HandyGraphFunctions.h"


//--------------------------- ValidNeighbour -----------------------------
//
//  returns true if x,y is a valid position in the map
//------------------------------------------------------------------------
bool ValidNeighbour( 	int x,
						int y,
						int NumCellsX,
						int NumCellsY ) {
	return !( ( x < 0 ) || ( x >= NumCellsX ) || ( y < 0 ) || ( y >= NumCellsY ) );
}
