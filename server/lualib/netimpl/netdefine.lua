local NETDEFINE = {
	HEARTBEAT = 0x70000001, 

	-- loginmgr
	LM_LOGIN_USER = 0x00010001, 
	LM_LOGIN_PLAYER = 0x00010002,
	LM_CREATE_PLAYER = 0x00010003, 

	-- gateway
	GW_PLAYER_ONLINE = 0X00050001,
	GW_PLAYER_MOVE = 0x00050002,
}

return NETDEFINE