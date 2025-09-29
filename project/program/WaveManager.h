#pragma once
#include"singleton.h"
#include<vector>
#include<string>
#include<memory>


class GameObject;
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

	//	タイマーの生成
	void createTimer();

	//	撃破数の表示
	void createKillCount();

public:
	void LoadData(int a_waveDataID);


	//	初期化
	void Initialize();

	//	更新
	void Update();

	//	時間を取得
	float GetTime()const { return startTime_; }

	//	時間を分：秒で文字列として取得
	std::string GetElapsedTimeFormatted()const;

	//	撃破数の文字列変換
	std::string GetKillCountFormatString()const;

	//	撃破数の加算
	void AddKillCount() {
		killCount_++;
	}

	int GetKillCount()const {
		return killCount_;
	}

private:
	//	タイマーの参照
	std::weak_ptr<GameObject> timer_;

	//	
	std::weak_ptr<GameObject> drawKill_;

	//	所持しているウェーブIDのコレクション
	std::vector<int> wave_ids_;

	//	ウェーブの必要な情報
	std::vector<WaveData> wave_entrys_;

	//	今のウェーブ番号
	int currentWaveNum_;

	//	キル数
	int killCount_;

	//	ウェーブ開始の時間
	float startTime_;
};
