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


	//	ダメージ
	void Damage(int a_damage) {
		assert(a_damage >= 0);
		current_hp_ -= a_damage;
		this->clamp();

	}

	//	体力が最大かどうか
	bool IsHealthMax()const {
		return current_hp_ == max_hp_;
	}

	//	体力の割合表示
	float Percent()const {
		return current_hp_ / max_hp_;
	}

	//	無敵時間の減少
	void Update()override {
		//	時間があったら
		if (current_invi_ > 0) {
			//	時間を減らす
			current_invi_ -= Time::deltaTime();
		}

		//	生存判定
		if (current_hp_ <= 0) {
			alive_.Set(Flag::Off);
		}
	}


	//	アクセサ
	void SetMaxInvi(const double& a_max_invi) { max_invi_ = a_max_invi; }
	void SetMaxHp(int a_max_hp) { max_hp_ = a_max_hp; }
	void SetCurrentInvi(const double& a_current_invi) { current_invi_ = a_current_invi; }

	//	取得
	int GetMaxHp()const { return max_hp_; }
	int GetCurrentHp()const { return current_hp_; }

protected:
	double current_invi_;	//	残りの無敵時間
	double max_invi_;		//	無敵時間の最大
	int current_hp_;		//	今の体力
	int max_hp_;			//	最大体力


public:
	Flag alive_;			//	生存判定
	Flag isInvincible_;		//	無敵判定
};