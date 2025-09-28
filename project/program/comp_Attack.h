#pragma once
#include"MonoBehaviour.h"
#include"Time.h"

class AttackComp : public MonoBehaviour {
public:

	AttackComp(int attack,double a_max_ct,int a_id)
		:attack_(attack), max_ct_(a_max_ct),ct_(a_max_ct),id_(a_id)
	{ }

	void Update()override {
		//if (ct_ > 0) {
		//	ct_ -= Time::deltaTime();
		//}
	}

	int Attack() {
		//if (ct_ > 0) return 0;
		//ct_ = max_ct_;
		return attack_;
	}

	//	アクセサ
	int GetID()const { return id_; }
	int GetCT()const { return ct_; }

protected:
	double max_ct_;
	double ct_;
	int attack_;
	int id_;
public:
	//	有効判定
	Flag enable = Flag::On;
};


