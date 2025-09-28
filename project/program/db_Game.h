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

	const EnemyData* GetEnemyData(int id)const {
		return enemyTable_.findById(id);
	}

	const AnimData* GetAnimData(int id)const {
		return animDataTable_.findById(id);
	}

	const EnemySizeData* GetEnemySizeData(int id)const {
		return enemySizeTable_.findById(id);
	}

	const WeaponData* GetWeaponData(int id)const {
		return weaponDataTable_.findById(id);
	}

	const ImageData* GetImageData(int id)const {
		return imageTable_.findById(id);
	}

	const DropExpData* GetDropExpData(int id)const {
		return dropExpTable_.findById(id);
	}

	const ExpTable* GetExpTable(int id)const {
		return expTable_.findById(id);
	}

	const WaveEnties* GetWaveEnties(int id)const {
		return waveEntryTable_.findById(id);
	}

	const WaveData* GetWaveData(int id)const {
		return waveDataTable_.findById(id);
	}

	const WeaponLevelData* GetWeaponLevelData(int weaponID, int level) {
		//	idに変換（例：310100 + 1 = 301101） 
		auto id = weaponID + 100 + level;
		return weaponLevelTable_.findById(id);
	}

	const WeaponIDList* GetWeaponIDTable(int id) {
		return weaponIDTable_.findById(id);
	}


private:
	DataTable<PlayerData> playerTable_;	//	プレイヤーデータテーブル
	DataTable<EnemyData> enemyTable_;	//	敵のデータテーブル
	DataTable<AnimData> animDataTable_;	//	アニメーションテーブル
	DataTable<EnemySizeData> enemySizeTable_;	//	敵のサイズデータ
	DataTable<WeaponData> weaponDataTable_;	//	武器データのテーブル
	DataTable<ImageData> imageTable_;	//	画像のデータテーブル
	DataTable<DropExpData> dropExpTable_;	//	ドロップする経験値のテーブル
	DataTable<ExpTable> expTable_;	//	経験値のテーブル
	DataTable<WaveEnties> waveEntryTable_;	//	ウェーブの制御データ
	DataTable<WaveData> waveDataTable_;	//	ウェーブのIDデータ
	DataTable<WeaponLevelData> weaponLevelTable_;	//	武器のレベルごとのデータ
	DataTable<WeaponIDList> weaponIDTable_;	//	使用可能な武器のID
};