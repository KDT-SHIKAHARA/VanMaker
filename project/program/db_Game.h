#pragma once
#include"singleton.h"
#include"DataTable.h"

/// �Q�[���S�̂̃f�[�^�x�[�X
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

private:
	DataTable<PlayerData> playerTable_;	//	�v���C���[�f�[�^�e�[�u��
	DataTable<EnemyData> enemyTable_;	//	�G�̃f�[�^�e�[�u��
};