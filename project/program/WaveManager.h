#pragma once
#include"singleton.h"
#include<vector>

//	ウェーブの切り替えと敵の生成の管理をする
class WaveManager : public Singleton<WaveManager> {
	friend class Singleton<WaveManager>;
	WaveManager();

	//	ウェーブの制御に必要な情報
	struct WaveData {
		int enemyID;	//	id
		int create_num;	//	出現数
		float interval;	//	生成間隔
		float timer;	//	経過時間
	};

	//	ウェーブの情報の読み込み
	void LoadWaveEntryData();

public:
	void LoadData(int a_waveDataID);


	//	初期化
	void Initialize();

	//	更新
	void Update();

	

private:
	//	所持しているウェーブIDのコレクション
	std::vector<int> wave_ids_;

	//	ウェーブの必要な情報
	std::vector<WaveData> wave_entrys_;

	//	今のウェーブ番号
	int currentWaveNum_;

	//	ウェーブ開始の時間
	float startTime_;
};
