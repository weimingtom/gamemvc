#ifndef PATHPLANNER_H
#define PATHPLANNER_H

//-----------------------------------------------------------------------------
//
//  Name:   CActor_PathPlanner.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to handle the creation of paths through a navigation graph
//-----------------------------------------------------------------------------
#include <list>
#include "navigation/TimeSlicedGraphAlgorithms.h"
#include "Graph/GraphAlgorithms.h"
#include "Graph/SparseGraph.h"
#include "navigation/PathEdge.h"
#include "PlayModel.h"

class CActorMapa;

class CActor_PathPlanner
{
private:

	//for legibility
	enum
	{
		no_closest_node_found = -1
	};

public:

	//for ease of use typdef the graph edge/node types used by the navgraph
	typedef PlayModel::NavGraph::EdgeType EdgeType;
	typedef PlayModel::NavGraph::NodeType NodeType;
	typedef std::list<PathEdge> Path;

private:

	//A pointer to the owner of this class
	CActorMapa* m_pOwner;

	//a reference to the navgraph
	const PlayModel::NavGraph& m_NavGraph;

	//a pointer to an instance of the current graph search algorithm.
	Graph_SearchTimeSliced<EdgeType>* m_pCurrentSearch;

	//this is the position the bot wishes to plan a path to reach
	Vector2D m_vDestinationPos;

	//returns the index of the closest visible and unobstructed graph node to
	//the given position
	int GetClosestNodeToPosition(Vector2D pos) const;

	//smooths a path by removing extraneous edges. (may not remove all
	//extraneous edges)
	void SmoothPathEdgesQuick(Path& path);

	//smooths a path by removing extraneous edges. (removes *all* extraneous
	//edges)
	void SmoothPathEdgesPrecise(Path& path);

	//called at the commencement of a new search request. It clears up the
	//appropriate lists and memory in preparation for a new search request
	void GetReadyForNewSearch();

public:

	CActor_PathPlanner(CActorMapa* owner);
	~CActor_PathPlanner();

	//creates an instance of the A* time-sliced search and registers it with
	//the path manager
	bool RequestPathToItem(unsigned int ItemType);

	//creates an instance of the Dijkstra's time-sliced search and registers
	//it with the path manager
	bool RequestPathToPosition(Vector2D TargetPos);

	//called by an agent after it has been notified that a search has terminated
	//successfully. The method extracts the path from m_pCurrentSearch, adds
	//additional edges appropriate to the search type and returns it as a list of
	//PathEdges.
	Path GetPath();

	//the path manager calls this to iterate once though the search cycle
	//of the currently assigned search algorithm. When a search is terminated
	//the method messages the owner with either the msg_NoPathAvailable or
	//msg_PathReady messages
	int CycleOnce() const;

	Vector2D GetDestination() const
	{
		return m_vDestinationPos;
	}
	void SetDestination(Vector2D NewPos)
	{
		m_vDestinationPos = NewPos;
	}

	//used to retrieve the position of a graph node from its index. (takes
	//into account the enumerations 'non_graph_source_node' and
	//'non_graph_target_node'
	Vector2D GetNodePosition(int idx) const;

	void Render();
};

#endif

