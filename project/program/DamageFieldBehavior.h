#pragma once
#include"MonoBehaviour.h"

//	�����p�R���|�[�l���g


class DamagerFieldBehaviour : public MonoBehaviour {
public:
	void Update()override;
private:
	float angle_speed_ = 0.01;
};
