#pragma once
#include"MonoBehaviour.h"

//	挙動用コンポーネント


class DamagerFieldBehaviour : public MonoBehaviour {
public:
	void Update()override;
private:
	float angle_speed_ = 0.01;
};
