#pragma once
#include<memory>
#include<vector>

#include"flag.h"

class GameObject;
//	�C���X�^���X(GameObject)�ƎQ�Ƃ̊Ǘ�
class WeaponBase {
public:
	//	������
	WeaponBase(double a_max_ct)
		:max_ct_(a_max_ct), current_ct_(0), enable_(Flag::On)
	{ }

	virtual ~WeaponBase() = default;

	//	����
	virtual void Fire() = 0;

	//	�X�V
	virtual void Update() = 0;

	//	�N�[���^�C�����o�߂��Ă��邩�ǂ���
	//	true: �o��	false: �N�[���^�C����
	bool IsReady() {
		return current_ct_ <= 0;
	}

protected:
	//	���������C���X�^���X�̎Q��
	std::vector<std::weak_ptr<GameObject>> attackObject_;

	//	�N�[���^�C��
	double max_ct_;

	//	�؂�ւ��p�̌o�ߎ���
	double current_ct_;
public:

	//	�L������
	Flag enable_;

};