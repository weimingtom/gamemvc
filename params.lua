
NumAgents            =     100

NumObstacles         =    7
MinObstacleRadius    =    40
MaxObstacleRadius    =    80

-- number of horizontal cells used for spatial partitioning
NumCellsX            =   7
-- number of vertical cells used for spatial partitioning
NumCellsY            =   7


-- how many samples the smoother will use to average a value
NumSamplesForSmoothing =  10


-- this is used to multiply the steering force AND all the multipliers
-- found in SteeringBehavior
SteeringForceTweaker    = 1.0

MaxHeadTurnRate			= 0.2
MaxSteeringForce        = 1.0
MaxSpeed                = 1.5	-- Tenia 1.0 
VehicleMass             = 1.0
VehicleScale            = 10.0	-- tenia 16.0

-- use these values to tweak the amount that each steering force
-- contributes to the total steering force
SeparationWeight         = 20.0	-- Tenia 10.0
AlignmentWeight          = 1.0
CohesionWeight           = 2.0
ObstacleAvoidanceWeight  = 10.0
WallAvoidanceWeight      = 20.0 -- tenia 10.0 
WanderWeight             = 1.0
SeekWeight               = 0.5
FleeWeight               = 1.0
ArriveWeight             = 1.0
PursuitWeight            = 1.0
OffsetPursuitWeight      = 1.0
InterposeWeight          = 1.0
HideWeight               = 1.0
EvadeWeight              = 0.01
FollowPathWeight         = 0.05

-- how close a neighbour must be before an agent perceives it (considers it
-- to be within its neighborhood)
ViewDistance             = 20.0 -- Tenia 15.0

-- used in obstacle avoidance
MinDetectionBoxLength    = 40.0

-- used in wall avoidance
WallDetectionFeelerLength = 40.0 

-- these are the probabilities that a steering behavior will be used
-- when the Prioritized Dither calculate method is used to sum
-- combined behaviors

prWallAvoidance      	=    0.5
prObstacleAvoidance     =    0.5
prSeparation            =    0.2
prAlignment             =    0.3
prCohesion              =    0.6
prWander                =    0.8
prSeek                  =    0.8
prFlee                  =    0.6
prEvade                 =    1.0
prHide                  =    0.8
prArrive                =    0.5

ShowObstacles=false
ShowDetectionBox=false	-- No usado?.
ShowWanderCircle=false  -- No usado?.
ShowFeelers=false       -- No usado?.
ShowSteeringForce=false -- No usado?.
ShowFPS=false           -- No usado?.
RenderNeighbors=false
ViewKeys=false			-- No usado?.
ShowCellSpaceInfo=false -- No usado?.
ShowWalls=true			-- Dibujar los muros.
ShowGraph=false			-- Dibuja grafo de busqueda para el pathfinder.
ShowBrain=false			-- Dibuja el brain de un Bot. ( El Path habitualmente ).
ShowPath=false			-- Dibujar el path calculado para un actor.

MaxSearchCyclesPerUpdateStep = 1000 
SmoothPathsQuick	= true	 
SmoothPathsPrecise	= false
