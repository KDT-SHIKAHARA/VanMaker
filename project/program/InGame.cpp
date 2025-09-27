#include "InGame.h"
#include "debugDef.h"
#include <cassert>


#include"PlayerFactory.h"
#include"EnemyFactory.h"

InGame::InGame()
{
}

void InGame::Initialize()
{
	//	ƒvƒŒƒCƒ„[¶¬
	auto player = PlayerFactory::CreatePlayer(100001);
	assert(player);
	player->transform_.SetPosition({ 400.0f,300.0f });
	AddGameObject(player);



	auto enemy = EnemyFactory::CreateEnemy(2001, 2001);
	enemy->transform_.SetPosition({ 700.f,400.0f });
	AddGameObject(enemy);

}

void InGame::Render()
{
	DEBUG_LOG("InGame");
}


