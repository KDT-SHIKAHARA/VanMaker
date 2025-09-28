#include"WaveManager.h"
#include"db_Game.h"
#include "Time.h"
#include"EnemyFactory.h"
#include"GameObjectRequestAdd.h"

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
	//	敵の情報ごとに追加
	for (const auto& Entry : data->entries) {
		wave_entrys_.emplace_back(Entry.enemyID, Entry.createNum, Entry.interval, 0);
	}
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

void  WaveManager::Update() {
	//	時間の取得
	const auto& dt = Time::deltaTime();

	//	時間を経過させる
	startTime_ += dt;

	//	データ取得
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


	//	サイズ未満なら
	if (currentWaveNum_ < wave_ids_.size()) {
		//	今の時間と次のインデックスの開始時間を見て
		if (startTime_ >= data->startTime) {

		}
	}


}