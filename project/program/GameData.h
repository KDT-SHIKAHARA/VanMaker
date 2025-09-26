#pragma once
#include<string>


//	�v���C���[�̃f�[�^�\��
struct PlayerData {
	int id;				//	�L������id
	std::string name;	//	���O
	int weaponId;	//	�����id
	int hp;			//	�̗͂̍ő�l
	float speed;	//	�ړ����x
	int expTableId;		//	�o���l�e�[�u����id
	float max_invi;	//	���G���Ԃ̐ݒu
	float size_w_;	//	�T�C�YW
	float size_h_;	//	�T�C�YH
};

//	�v���C���[�̃A�j���[�V�����p�̃f�[�^
struct AnimData {
	int id;				//	���ʗpid
	std::string name;	//	�A�j���[�V�����̖��O
	std::string filePath;	//	�摜�t�@�C���p�X
	int animFirstFrame;	//	�A�j���[�V�����̍ŏ��̔ԍ�
	int animLastFrame;	//	�A�j���[�V�����̍Ō�̔ԍ�
	int layer;		//	�`�惌�C���[
};

//	�G�L�����̃f�[�^�\��
struct EnemyData {
	int id;	//	�f�[�^ID
	int sizeTypeId;	//	�T�C�Y�e�[�u��
	int hp;	//	�̗�
	int	attack;	//	�U����
	int behaviorId;		//	�����p�^�[��
	int dropExpId;	//	�h���b�v����o���l�̃e�[�u��
};

struct EnemySizeData {
	int id;
	int base_width;
	int base_height;
	float exrate;
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


