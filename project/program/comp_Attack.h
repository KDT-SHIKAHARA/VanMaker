#pragma once
#include"MonoBehaviour.h"
#include"Time.h"

class AttackComp : public MonoBehaviour {
public:

	AttackComp(int attack,double a_max_ct)
		:attack_(attack), max_ct_(a_max_ct), ct_(0)
	{ }

	void Update()override {
		if (ct_ > 0) {
			ct_ -= Time::deltaTime();
		}
	}

	int Attack() {
		if (ct_ > 0) return 0;
		ct_ = max_ct_;
		return attack_;
	}

protected:
	double max_ct_;
	double ct_;
	int attack_;
public:
	//	—LŒø”»’è
	Flag enable = Flag::On;
};


