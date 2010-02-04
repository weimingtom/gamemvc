/*
 * PlayModel.h
 *
 *  Created on: 04/01/2010
 *      Author: 79481180
 */

#ifndef PLAYMODEL_H_
#define PLAYMODEL_H_

#include <memory>
namespace gcn{

	class Graphics;

}
#include <mvc/Model.h>

#include "Tile.h"

class PlayModel: public Model
{
public:
	PlayModel();
	virtual ~PlayModel();

	void getTileIso();
	void getTileHex();
	void getTileSquared();

	void draw(	gcn::Graphics* graphic, gcn::Point p);


private:

	std::auto_ptr<Tile> ptTile;

};

#endif /* PLAYMODEL_H_ */
