#pragma once
#include"WeaponBase.h"

//	�_���[�W�t�B�[���h�i�j���j�N�݂����ȁj�̐����N���X
class DamageField : public WeaponBase {
public:

	//	GameObject�̐���

	//	�����̃N�[���^�C���Ȃǂ̊Ǘ�

	DamageField();
	void Initialize()override;
	void Fire()override;
	void Update()override;
protected:
	//	�C���X�^���X�̐���
	void create();
};