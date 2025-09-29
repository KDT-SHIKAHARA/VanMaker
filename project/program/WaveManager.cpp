#include"WaveManager.h"
#include"db_Game.h"
#include "Time.h"
#include"EnemyFactory.h"
#include"GameObjectRequestAdd.h"
#include"GameObject.h"
#include"data_Window.h"

#include"text.h"
#include"GetColor.h"

//	フォルダからウェーブ番号
WaveManager::WaveManager()
	:currentWaveNum_(0),startTime_(0)
{

}

//	今のウェーブ番号の情報の読込
void WaveManager::LoadWaveEntryData()
{
	//	今のウェーブデータ全体取得
	auto data = GameDataBase::Instance().GetWaveEnties(wave_ids_[currentWaveNum_]);

	//	中身が存在していたら
	if (!wave_entrys_.empty()) {
		wave_entrys_.clear();
	}

	//	敵の情報ごとに追加
	for (const auto& Entry : data->entries) {
		wave_entrys_.emplace_back(Entry.enemyID, Entry.createNum, Entry.interval, 0);
	}
}

void WaveManager::createTimer()
{
	//	インスタンス生成
	auto obj = std::make_shared<GameObject>();

	//	文字列クラスの作成
	obj->AddComponent<Text>(GetElapsedTimeFormatted(),WHITE,true,35);

	//	座標設定
	obj->transform_.SetWorldPosition(Vector2Df{(float)WindowData::m_sceneW / 2,100.f });

	timer_ = obj;

	GameObjectQueue::Instance().Enqueue(obj);
}

void WaveManager::createKillCount()
{
	//	インスタンス生成
	auto obj = std::make_shared<GameObject>();
	obj->AddComponent<Text>(GetKillCountFormatString(), WHITE, true, 20);
	obj->transform_.SetWorldPosition(Vector2Df{ (float)WindowData::m_sceneW-200,100.f });
	drawKill_ = obj;
	GameObjectQueue::Instance().Enqueue(obj);

}

//	このステージのウェーブ番号を取得
void WaveManager::LoadData(int a_waveDataID)
{
	//	データ
	auto data = GameDataBase::Instance().GetWaveData(a_waveDataID);

	//	中身が存在していたら消す
	if (!wave_ids_.empty()) {
		wave_ids_.clear();
	}

	//	登録されているウェーブ番号の追加
	for (const auto& waveID : data->wave_id){
		wave_ids_.push_back(waveID);
	}

	//	最初のデータの取得
	LoadWaveEntryData();
}

void WaveManager::Initialize()
{
	currentWaveNum_ = 0;
	startTime_ = 0;
	killCount_ = 0;

	//	テーブルデータ取得
	LoadWaveEntryData();

	//	タイマー作成
	createTimer();

	//	キル数
	createKillCount();
}

void  WaveManager::Update() {
	//	時間の取得
	const auto& dt = Time::deltaTime();

	//	時間を経過させる
	startTime_ += dt;

	//	表示用の時間を更新
	timer_.lock()->GetComponent<Text>()->SetText(GetElapsedTimeFormatted());

	//	キル数の表示更新
	drawKill_.lock()->GetComponent<Text>()->SetText(GetKillCountFormatString());


	//	今のウェーブデータ取得
	auto data = GameDataBase::Instance().GetWaveEnties(wave_ids_[currentWaveNum_]);


	//	敵の種類分
	for (auto& entry : wave_entrys_) {
		//	時間を経過
		entry.timer += dt;

		//	時間が生成タイミングを越していたら処理をする
		if (entry.timer >= entry.interval) {
			//	1回の生成分処理を行う
			for (size_t i = 0; i < entry.create_num; i++) {
				auto enemy = EnemyFactory::CreateEnemy(entry.enemyID);
				GameObjectQueue::Instance().Enqueue(enemy);

			}

			//	時間をリセット
			entry.timer = 0;
		}

	}


	//	最後のウェーブ未満の時
	if (currentWaveNum_ + 1 < wave_ids_.size()) {
		//	次のデータ取得
		auto next_data = GameDataBase::Instance().GetWaveEnties(wave_ids_[currentWaveNum_ + 1]);

		//	次の開始時間になっていたら
		if (startTime_ >= next_data->startTime) {
			//	ウェーブ番号を次へ
			currentWaveNum_++;

			//	ウェーブデータの読み込み
			LoadWaveEntryData();
		}

	}


}

/// <summary>
/// 時間を分：秒で取得する
/// </summary>
/// <returns></returns>
std::string WaveManager::GetElapsedTimeFormatted() const
{
	int totalSec = static_cast<int>(startTime_);
	int minutes = totalSec / 60;
	int seconds = totalSec % 60;

	char buf[16];
	snprintf(buf, sizeof(buf), "%02d:%02d", minutes, seconds);
	return std::string(buf);
}

std::string WaveManager::GetKillCountFormatString() const
{
	std::string text = "撃破数:" + std::to_string(killCount_);
	return text;
}




