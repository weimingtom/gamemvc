/*
 * Tile.h
 *
 *  Created on: 01/01/2010
 *      Author: uberiain
 */

#ifndef TILE_H_
#define TILE_H_

#include <guichan.hpp>

class Tile
{
public:

	Tile( const std::string& tile );

	~Tile();
	int getWidth();
	int getHeight();
	void draw( 	gcn::Graphics* graphic,
				gcn::Point p );
	gcn::Color getPixel( 	int x,
							int y );
private:

	gcn::Image* m_Tile;
	gcn::Point m_anchor;

};

#endif /* TILE_H_ */
