#pragma once
#include"singleton.h"
#include"DataTable.h"

/// ゲーム全体のデータベース
class GameDataBase : public Singleton<GameDataBase> {
	friend class Singleton<GameDataBase>;
	GameDataBase();
	~GameDataBase() = default;
public:

	const PlayerData* GetPlayerData(int id) const {
		return playerTable_.findById(id);
	}

private:
	DataTable<PlayerData> playerTable_;	//	プレイヤーデータテーブル
};