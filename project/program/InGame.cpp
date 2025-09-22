#include "InGame.h"
#include "debugDef.h"
#include "db_Game.h"
#include <cassert>

InGame::InGame()
{
	auto playerData = GameDataBase::Instance().GetPlayerData(100001);
	assert(playerData);
}

void InGame::Initialize()
{
}

void InGame::Render()
{
	DEBUG_LOG("InGame");
}


