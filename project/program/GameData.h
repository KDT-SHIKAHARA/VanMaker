#pragma once
#include<string>


//	�v���C���[�̃f�[�^�\��
struct PlayerData {
	int id;				//	�L������id
	std::string name;	//	���O
	std::string filePath;	//	�摜�t�@�C���p�X
	int weaponId;	//	�����id
	int hp;			//	�̗͂̍ő�l
	int expTableId;		//	�o���l�e�[�u����id
};


//	�G�L�����̃f�[�^�\��
struct EnemyData {
	int id;	//	�f�[�^ID
	std::string name;	//	���O
	std::string texturePath;	//	�摜�t�@�C���p�X
	int sizeTypeId;	//	�T�C�Y�e�[�u��
	int hp;	//	�̗�
	int	attack;	//	�U����
	int behaviorId;		//	�����p�^�[��
	int dropExpId;	//	�h���b�v����o���l�̃e�[�u��
};

// ����̃f�[�^�\��
struct WeaponData {
	int id;	//	�f�[�^ID
	std::string name;	//	���O
	std::string texturePath;	//	�摜�t�@�C���p�X
	int attack;	//	�U����
	float attackInterval;	//	�U���Ԋu
	int behaviorId;	//	����p�^�[��
};

//	�G�L�����̃T�C�Y�f�[�^�\��
struct EnemySizeType {
	int id;	//	�f�[�^ID
	float scale;	//	�\���X�P�[��
};

//	�o���l�̃e�[�u���f�[�^�\��
struct ExpTable {
	int level;	//	���x��
	int requiredExp;	//	�K�v�o���l
};


