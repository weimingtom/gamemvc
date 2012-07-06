class "Aldeano" (CActorMapa)
--
--	pGame: 			Puntero a la clase GameWorld.
--	laPosicion:		Posicion dentro del mapa donde esta el Actor.
--	elActorTipo:	El Actor tipo del cual obtenemos los frames.
--
function Aldeano:__init(pGame,laPosicion,elActorTipo)
	CActorMapa.__init(self,pGame,laPosicion,elActorTipo)

	self.m_Personality = "none"
	self:SmoothingOn()					-- Mas suave???
	self.m_pSteering:WallAvoidanceOn()
	self.m_pBrain = Aldeano_Think(self)
	
end

function Aldeano:UpdateFrame(iElapsedTicks)
	
	CActorMapa.UpdateFrame(self,iElapsedTicks)
	
end

function Aldeano:HandleMessage(msg)

--	print("En Aldeano:HandleMessage")
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

class "Aldeano_Think" (Goal_Think)

function Aldeano_Think:__init(pBot)
	Goal_Think.__init(self,pBot)
	
	self.time = -1	-- Tiempo nulo
	self.m_pOwner.m_State ="stopped"
	self.m_pOwner.m_Dir = self.m_pOwner:isHeadingAt()
	self.m_pOwner.m_iFrame = 0
		
end
function Aldeano_Think:Arbitrate()

-- Mover el aldeano de una forma aleatoria por todo el mapa.
--	if (self.time < 0 ) then
	
--		self.time = Clock:GetCurrentTime()	-- Utilizar tiempo aleatorio para moverse

--	else
	
--		local now = Clock:GetCurrentTime()
--		if ((now - self.time) > math.random(1200)) then
	
--			self.time = now
--			local p = Vector2D(math.random(0,self.m_pOwner:World():cxClient()),math.random(0,self.m_pOwner:World():cxClient()))
--			self:RemoveAllSubgoals()
--			self:AddSubgoal(Goal_MoveToPosition(self.m_pOwner,p))
--			self.time = -1
		
--		end
		
--	end
	
end