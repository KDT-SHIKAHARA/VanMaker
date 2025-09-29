#include "InGame.h"
#include "debugDef.h"
#include <cassert>

#include"PlayerFactory.h"
#include"EnemyFactory.h"
#include"WaveManager.h"
#include"data_Window.h"
#include"script_InGameWave.h"
#include"InfiniteBackground.h"
#include"db_Game.h"
#include"filePath.h"
#include"system_EventBus.h"
#include"BGMSystem.h"

InGame::InGame()
{
	scripts_.push_back(std::make_unique<InGameWaveScript>());

	//	後でステージIDを受け取ってください。
	stageID_ = 801001;
}

void InGame::Initialize()
{
	//	ステージのデータ読み込み
	auto stageID = GameDataBase::Instance().GetStageData(stageID_);


	//	背景の生成
	auto bghandle = GameDataBase::Instance().GetImageData(stageID->bg_id);
	auto bg = std::make_shared<GameObject>();
	bg->AddComponent<InfiniteBackground>(bghandle->filePath);
	AddGameObject(bg);

	//	プレイヤー生成
	auto player = PlayerFactory::CreatePlayer(100001);
	assert(player);
	player->transform_.SetPosition({(float)WindowData::m_sceneW,(float)WindowData::m_sceneH});
	AddGameObject(player);



	//	とりあえず仮で読み込んでみます
	int wave_number = 4001;
	WaveManager::Instance().LoadData(wave_number);
	WaveManager::Instance().Initialize();

	//	音を鳴らす
	EventBus::Instance().Publish(PlayBGMEvent{ SH_FilePath::stage_bgm,-1,2 });
	BGMSystem::Instance().SetVolume(2, 250);


}

void InGame::Render()
{
	DEBUG_LOG("InGame");
}

void InGame::End()
{
	EventBus::Instance().Publish(StopBGMEvent{ 2 });

}


