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
	DataTable<PlayerData> playerTable_;	//	�v���C���[�f�[�^�e�[�u��
	DataTable<EnemyData> enemyTable_;	//	�G�̃f�[�^�e�[�u��
	DataTable<AnimData> animDataTable_;	//	�A�j���[�V�����e�[�u��
	DataTable<EnemySizeData> enemySizeTable_;	//	�G�̃T�C�Y�f�[�^
	DataTable<WeaponData> weaponDataTable_;	//	����f�[�^�̃e�[�u��
	DataTable<ImageData> imageTable_;	//	�摜�̃f�[�^�e�[�u��
	DataTable<DropExpData> dropExpTable_;	//	�h���b�v����o���l�̃e�[�u��
	DataTable<ExpTable> expTable_;	//	�o���l�̃e�[�u��
};