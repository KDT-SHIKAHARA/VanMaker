#include "InGame.h"
#include "debugDef.h"
#include <cassert>


#include"PlayerFactory.h"
#include"EnemyFactory.h"
#include"WaveManager.h"

#include"script_InGameWave.h"

InGame::InGame()
{
	scripts_.push_back(std::make_unique<InGameWaveScript>());
}

void InGame::Initialize()
{
	//	ÉvÉåÉCÉÑÅ[ê∂ê¨
	auto player = PlayerFactory::CreatePlayer(100001);
	assert(player);
	player->transform_.SetPosition({ 400.0f,300.0f });
	AddGameObject(player);



	auto enemy = EnemyFactory::CreateEnemy(2001);
	enemy->transform_.SetPosition({ 700.f,400.0f });
	AddGameObject(enemy);

	//	Ç∆ÇËÇ†Ç¶Ç∏âºÇ≈ì«Ç›çûÇÒÇ≈Ç›Ç‹Ç∑
	int wave_number = 4001;
	WaveManager::Instance().LoadData(wave_number);

}

void InGame::Render()
{
	DEBUG_LOG("InGame");
}


