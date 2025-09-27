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

private:
	DataTable<PlayerData> playerTable_;	//	プレイヤーデータテーブル
	DataTable<EnemyData> enemyTable_;	//	敵のデータテーブル
	DataTable<AnimData> animDataTable_;	//	アニメーションテーブル
	DataTable<EnemySizeData> enemySizeTable_;	//	敵のサイズデータ
	DataTable<WeaponData> weaponDataTable_;	//	武器データのテーブル
	DataTable<ImageData> imageTable_;	//	画像のデータテーブル
	DataTable<DropExpData> dropExpTable_;	//	ドロップする経験値のテーブル
	DataTable<ExpTable> expTable_;	//	経験値のテーブル
};