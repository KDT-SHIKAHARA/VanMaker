#include "InGame.h"
#include "debugDef.h"
#include <cassert>


#include"PlayerFactory.h"
#include"EnemyFactory.h"
#include"WaveManager.h"
#include"data_Window.h"

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
	player->transform_.SetPosition({(float)WindowData::m_sceneW,(float)WindowData::m_sceneH});
	AddGameObject(player);

	//	Ç∆ÇËÇ†Ç¶Ç∏âºÇ≈ì«Ç›çûÇÒÇ≈Ç›Ç‹Ç∑
	int wave_number = 4001;
	WaveManager::Instance().LoadData(wave_number);
	WaveManager::Instance().Initialize();


}

void InGame::Render()
{
	DEBUG_LOG("InGame");
}


