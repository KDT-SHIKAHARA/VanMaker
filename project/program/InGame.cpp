#include "InGame.h"
#include "debugDef.h"
#include <cassert>


#include"PlayerFactory.h"

InGame::InGame()
{
	//	ƒvƒŒƒCƒ„[¶¬
	auto player = PlayerFactory::CreatePlayer(100001);
	assert(player);
	player->transform_.SetPosition({ 400.0f,300.0f });
	AddGameObject(player);
}

void InGame::Initialize()
{
}

void InGame::Render()
{
	DEBUG_LOG("InGame");
}


