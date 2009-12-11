#include "Goal_FollowPath.h"

#include "../CActorMapa.h"
#include "../PlayModel.h"

#include "Goal_TraverseEdge.h"

// #include "Graphics/SDLgdi.h"

//------------------------------ ctor -----------------------------------------
//-----------------------------------------------------------------------------
Goal_FollowPath::Goal_FollowPath( CActorMapa* pBot, std::list < PathEdge > path ) :
	Goal_Composite < CActorMapa > ( pBot, goal_follow_path ),
	m_Path( path ) {

	std::list<PathEdge>::iterator i;
	std::cout << "Path a seguir: ";
	for (i=m_Path.begin();i!=m_Path.end();++i ){

		std::cout << "From : " << (*i).Source();
		std::cout << " To : " << (*i).Destination();

	}
	std::cout << std::endl;
}

//------------------------------ Activate -------------------------------------
//-----------------------------------------------------------------------------
void Goal_FollowPath::Activate() {
	m_iStatus = active;

	//get a reference to the next edge
	PathEdge edge = m_Path.front();

	//remove the edge from the path
	m_Path.pop_front();

	//some edges specify that the bot should use a specific behavior when
	//following them. This switch statement queries the edge behavior flag and
	//adds the appropriate goals/s to the subgoal list.
	switch ( edge.Behavior() ) {
		case NavGraphEdge::normal: {
			AddSubgoal( new Goal_TraverseEdge( m_pOwner, edge, m_Path.empty() ) );
		}

		break;

		case NavGraphEdge::jump: {
			//add subgoal to jump along the edge
		}

		break;

		case NavGraphEdge::grapple: {
			//add subgoal to grapple along the edge
		}

		break;

		default:

			throw std::runtime_error( "<Goal_FollowPath::Activate>: Unrecognized edge type" );
	}
}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_FollowPath::Process() {

	std::cout << "Goal_FollowPath::Process" << std::endl;
	std::cout << " ++ ";

	//if status is inactive, call Activate()
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	//if there are no subgoals present check to see if the path still has edges.
	//remaining. If it does then call activate to grab the next edge.
	if ( m_iStatus == completed && !m_Path.empty() ) {
		Activate();
	}

	return m_iStatus;
}

//---------------------------- Render -----------------------------------------
//-----------------------------------------------------------------------------
void Goal_FollowPath::Render() {
/*
	//render all the path waypoints remaining on the path list
	std::list < PathEdge >::iterator it;
	for ( it = m_Path.begin(); it != m_Path.end(); ++it ) {
		gdi->SetPenColor(CColor::Black);
		//    gdi->LineWithArrow(it->Source(), it->Destination(), 5);
		gdi->LineISO( it->Source(), it->Destination() );
		//		gdi->RedBrush();
		gdi->SetPenColor(CColor::Black);
		gdi->CircleISO( it->Destination(), 3 );
	}

	//forward the request to the subgoals
	Goal_Composite < CActorMapa >::Render();
*/
}

