class "Harry" (CActorMapa)
--
--	pGame: 			Puntero a la clase GameWorld.
--	laPosicion:		Posicion dentro del mapa donde esta el Actor.
--	elActorTipo:	El Actor tipo del cual obtenemos los frames.
--
function Harry:__init(pGame,laPosicion,elActorTipo)
	CActorMapa.__init(self,pGame,laPosicion,elActorTipo)

	print("[Harry] constructor")
	self.m_Personality="none"
	self:SmoothingOn()					-- Mas suave???
	self.m_pSteering:WallAvoidanceOn()
	self.m_pBrain = Harry_Think(self)
end

function Harry:HandleMessage(msg)

--	print("En Harry:HandleMessage")
	if ( CActorMapa.HandleMessage(self,msg) ) then
	
		return true
		
	elseif (msg.Msg == CActorMapa.Msg_Goto ) then

		local p = Vector2D(msg.ExtraInfo.x,msg.ExtraInfo.y) 
		self.m_pBrain:RemoveAllSubgoals()
		self.m_pBrain:AddSubgoal(Goal_MoveToPosition(self,p))
		return true
		
	else
	
		return false
		
	end 
	
end

class "Harry_Think" (Goal_Think)

function Harry_Think:__init(pBot)
	Goal_Think.__init(self,pBot)
	
	self.time = Clock:GetCurrentTime()
	self.m_pOwner.m_State ="stopped"
	self.m_pOwner.m_Dir = self.m_pOwner:isHeadingAt()
	self.m_pOwner.m_iFrame = 0

end

function Harry_Think:Arbitrate()
	
--	print("[Harry_Think] Arbitrate")
	local time = Clock:GetCurrentTime()
	local trans =  time - self.time
	if trans > 10 then

		self.time = time
		self:RemoveAllSubgoals()
		self:AddSubgoal(Goal_Wander(self.m_pOwner))
		
	end
	
end