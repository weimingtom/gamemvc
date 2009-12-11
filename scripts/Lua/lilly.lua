class "Lilly" (CActorMapa)
--
--	pGame: 			Puntero a la clase GameWorld.
--	laPosicion:		Posicion dentro del mapa donde esta el Actor.
--	elActorTipo:	El Actor tipo del cual obtenemos los frames.
--
function Lilly:__init(pGame,laPosicion,elActorTipo)
	CActorMapa.__init(self,pGame,laPosicion,elActorTipo)

	self.m_Personality="none"
	self.m_State="stopped"
	self.m_Dir=self:isHeadingAt()		-- "S"
	self.m_iFrame =0
	self:SmoothingOn()					-- Mas suave???
	self.m_pSteering:WallAvoidanceOn()
	self.m_pBrain = Goal_Think(self)
--	print("Fin init lilly")

end

function Lilly:HandleMessage(msg)

--	print("En Lilly:HandleMessage")
	if ( CActorMapa.HandleMessage(self,msg) ) then
	
		return true
		
	elseif (msg.Msg == CActorMapa.Msg_Goto ) then

--		local info = class_info(msg.ExtraInfo)
--		print("Datos info = ", info.name)
		local p = Vector2D(msg.ExtraInfo.x,msg.ExtraInfo.y) 
		self.m_pBrain:RemoveAllSubgoals()
		self.m_pBrain:AddSubgoal(Goal_MoveToPosition(self,p))
		return true
		
	else
	
		return false
		
	end 
	
end

class "Lilly_Think" (Goal_Think)

function Lilly_Think:__init(pBot)
	Goal_Think.__init(self,pBot)
	
end
	