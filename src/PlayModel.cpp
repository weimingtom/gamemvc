/*
 * PlayModel.cpp
 *
 *  Created on: 04/01/2010
 *      Author: 79481180
 */

#include "PlayModel.h"

PlayModel::PlayModel() :
	Model() {

}

PlayModel::~PlayModel() {

}
void PlayModel::getTileIso() {
	ptTile.reset( new Tile( "Tile_Iso1.png" ) );
}
void PlayModel::getTileHex() {
	ptTile.reset( new Tile( "Tile_Hex.png" ) );
}
void PlayModel::getTileSquared() {
	ptTile.reset( new Tile( "Tile_Squared.png" ) );
}
void PlayModel::draw( 	gcn::Graphics* graphic,
						gcn::Point p ) {

	ptTile->draw( 	graphic,
					p );

}
