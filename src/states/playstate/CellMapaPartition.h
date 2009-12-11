/*
 * CellMapaPartition.h
 *
 *  Created on: 29-dic-2008
 *      Author: 79481180
 */

#ifndef CELLMAPAPARTITION_H_
#define CELLMAPAPARTITION_H_

#include <vector>
#include <list>

#include "2d/Vector2D.h"
#include "2d/InvertedAABBox2D.h"

#include "game/BaseGameEntity.h"

template < class entity >
struct CellMapa
{

	//all the entities inhabiting this cell
	std::list < entity > Members;

	//the cell's bounding box (it's inverted because the Window's default
	//co-ordinate system has a y axis that increases as it descends)
	InvertedAABBox2D BBox;

	CellMapa( 	Vector2D topleft,
				Vector2D botright ) :
		BBox( InvertedAABBox2D( topleft, botright ) ) {
	}

};

template < class entity >
class CellMapaPartition
{
public:
	CellMapaPartition( 	double width, //width of 2D space
						double height,
						int cellsX, //number of cells horizontally
						int cellsY //number of cells vertically
			);
	virtual ~CellMapaPartition();

	void AddEntity( const entity& ent );
	void UpdateEntity(	const entity& ent,
						Vector2D OldPos );

	CellMapa<entity> GetCell( Vector2D Pos );
	CellMapa<entity> GetCell( int pos );

	int PositionToIndex( const Vector2D& pos ) const;

private:

	std::vector < CellMapa < entity > > m_CellsMapa; //! Celdas del mapa a tratar.

	//the width and height of the world space the entities inhabit
	double m_dSpaceWidth;
	double m_dSpaceHeight;

	//the number of cells the space is going to be divided up into
	int m_iNumCellsX;
	int m_iNumCellsY;

	double m_dCellSizeX;
	double m_dCellSizeY;



};

template < class entity >
CellMapaPartition < entity >::CellMapaPartition( 	double width, //width of 2D space
													double height,
													int cellsX, //number of cells horizontally
													int cellsY ) ://number of cells vertically
	m_dSpaceWidth( width ),
	m_dSpaceHeight( height ),
	m_iNumCellsX( cellsX ),
	m_iNumCellsY( cellsY ) {

	//calculate bounds of each cell
	m_dCellSizeX = width / cellsX;
	m_dCellSizeY = height / cellsY;

	//create the cells
	for ( int y = 0; y < m_iNumCellsY; ++y ) {
		for ( int x = 0; x < m_iNumCellsX; ++x ) {
			double left = x * m_dCellSizeX;
			double right = left + m_dCellSizeX;
			double top = y * m_dCellSizeY;
			double bot = top + m_dCellSizeY;

			m_CellsMapa.push_back( CellMapa < entity > ( 	Vector2D( left, top ),
															Vector2D( 	right,
																		bot ) ) );
		}
	}

}

template < class entity >
CellMapaPartition < entity >::~CellMapaPartition() {

}

template < class entity >
int CellMapaPartition < entity >::PositionToIndex( const Vector2D& pos ) const {

	int idx = (int) ( m_iNumCellsX * pos.x / m_dSpaceWidth )
			+ ( (int) ( ( m_iNumCellsY ) * pos.y / m_dSpaceHeight )
					* m_iNumCellsX );

	//if the entity's position is equal to vector2d(m_dSpaceWidth, m_dSpaceHeight)
	//then the index will overshoot. We need to check for this and adjust
	if ( idx > (int) m_CellsMapa.size() - 1 )
		idx = (int) m_CellsMapa.size() - 1;

	return idx;

}

//----------------------- AddEntity --------------------------------------
//
//  Used to add the entitys to the data structure
//------------------------------------------------------------------------
template < class entity >
void CellMapaPartition < entity >::AddEntity( const entity& ent ) {
	// assert (ent);

	int idx = PositionToIndex( ent->Pos() );

	m_CellsMapa[idx].Members.push_back( ent );
}
//----------------------- UpdateEntity -----------------------------------
//
//  Checks to see if an entity has moved cells. If so the data structure
//  is updated accordingly
//------------------------------------------------------------------------
template < class entity >
void CellMapaPartition < entity >::UpdateEntity(	const entity& ent,
													Vector2D OldPos ) {
	//if the index for the old pos and the new pos are not equal then
	//the entity has moved to another cell.
	int OldIdx = PositionToIndex( OldPos );
	int NewIdx = PositionToIndex( ent->Pos() );

	if ( NewIdx == OldIdx )
		return;

	//the entity has moved into another cell so delete from current cell
	//and add to new one
	m_CellsMapa[OldIdx].Members.remove( ent );
	m_CellsMapa[NewIdx].Members.push_back( ent );
}

template < class entity >
CellMapa<entity> CellMapaPartition < entity >::GetCell( Vector2D pos ) {

	return m_CellsMapa[PositionToIndex( pos )];

}

template < class entity >
CellMapa<entity> CellMapaPartition < entity >::GetCell( int pos ) {

	return m_CellsMapa[pos];

}

#endif /* CELLMAPAPARTITION_H_ */
