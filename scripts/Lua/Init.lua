-------------------------------------------------------------------------------
-- Inicializacion datos lua
-------------------------------------------------------------------------------
math.randomseed( os.time() )

function is_value(t,v)
   for _,tv in pairs(t) do
       if  tv==v then return true end
   end
   return false
end

-- 
-- Enum types
--
SEND_MSG_IMMEDIATELY= 0
NO_ADDITIONAL_INFO	= nil

