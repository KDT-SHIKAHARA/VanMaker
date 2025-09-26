#pragma once
#include<algorithm>
#include<cassert>
#include"MonoBehaviour.h"
#include"flag.h"
#include"Time.h"

class Health : public MonoBehaviour {
protected:
	void clamp() { current_hp_ = std::clamp(current_hp_, 0, max_hp_); }
public:

	Health(const double& a_max_invi, int a_max_hp)
		:max_invi_(a_max_invi), max_hp_(a_max_hp), current_hp_(a_max_hp), current_invi_(0)
	{
	}

	virtual ~Health() = default;


	//	�_���[�W
	void Damage(int a_damage) {
		assert(a_damage >= 0);
		current_hp_ -= a_damage;
		this->clamp();

	}

	//	�̗͂��ő傩�ǂ���
	bool IsHealthMax()const {
		return current_hp_ == max_hp_;
	}

	//	�̗͂̊����\��
	float Percent()const {
		return current_hp_ / max_hp_;
	}

	//	���G���Ԃ̌���
	void Update()override {
		//	���Ԃ���������
		if (current_invi_ > 0) {
			//	���Ԃ����炷
			current_invi_ -= Time::deltaTime();
		}

		//	��������
		if (current_hp_ <= 0) {
			alive_.Set(Flag::Off);
		}
	}


	//	�A�N�Z�T
	void SetMaxInvi(const double& a_max_invi) { max_invi_ = a_max_invi; }
	void SetMaxHp(int a_max_hp) { max_hp_ = a_max_hp; }
	void SetCurrentInvi(const double& a_current_invi) { current_invi_ = a_current_invi; }

	//	�擾
	int GetMaxHp()const { return max_hp_; }
	int GetCurrentHp()const { return current_hp_; }

protected:
	double current_invi_;	//	�c��̖��G����
	double max_invi_;		//	���G���Ԃ̍ő�
	int current_hp_;		//	���̗̑�
	int max_hp_;			//	�ő�̗�


public:
	Flag alive_;			//	��������
	Flag isInvincible_;		//	���G����
};