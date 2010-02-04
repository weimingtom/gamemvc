/*
 * Tile.cpp
 *
 *  Created on: 01/01/2010
 *      Author: uberiain
 */
#include "Tile.h"

Tile::Tile(const std::string& tile) {

	m_Tile = gcn::Image::load( tile );
	m_anchor.set(	m_Tile->getWidth()/2,
					m_Tile->getHeight()/2 );
}

Tile::~Tile() {

	delete m_Tile;

}
int Tile::getWidth() {
	return m_Tile->getWidth();
}
int Tile::getHeight() {
	return m_Tile->getHeight();
}
void Tile::draw(gcn::Graphics* graphic,
				gcn::Point p) {

    graphic->drawImage( m_Tile,
				p.x - m_anchor.x,
				p.y - m_anchor.y );
}
gcn::Color Tile::getPixel(	int x,
							int y) {

	return m_Tile->getPixel( 	x,
								y );

}
