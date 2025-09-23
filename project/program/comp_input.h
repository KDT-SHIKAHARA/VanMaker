#pragma once
#include"Component.h"
#include"MonoBehaviour.h"
#include"vector2d.h"
#include"flag.h"

/// <summary>
/// ���[�U�[���͂���������R���|�[�l���g�N���X�ł��B
/// </summary>
class InputComponent : public MonoBehaviour {
public:
	void Update() override;
	Vector2Df GetDirection()const { return direction_; }
private:
	Vector2Df direction_;	//	���͕���
public:
	Flag isMove_ = Flag::Off;	//	���͂���Ă��邩�ǂ���
	Flag canInput_ = Flag::On;	//	���͉\�t���O
};
