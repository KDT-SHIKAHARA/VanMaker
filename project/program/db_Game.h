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

	const AnimData* GetAnimData(int id)const {
		return animDataTable_.findById(id);
	}

	const EnemySizeData* GetEnemySizeData(int id)const {
		return enemySizeTable_.findById(id);
	}

private:
	DataTable<PlayerData> playerTable_;	//	�v���C���[�f�[�^�e�[�u��
	DataTable<EnemyData> enemyTable_;	//	�G�̃f�[�^�e�[�u��
	DataTable<AnimData> animDataTable_;	//	�A�j���[�V�����e�[�u��
	DataTable<EnemySizeData> enemySizeTable_;
};