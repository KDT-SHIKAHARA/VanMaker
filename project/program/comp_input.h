#pragma once
#include"Component.h"
#include"MonoBehaviour.h"
#include"vector2d.h"
#include"flag.h"

/// <summary>
/// ユーザー入力を処理するコンポーネントクラスです。
/// </summary>
class InputComponent : public MonoBehaviour {
public:
	void Update() override;
	Vector2Df GetDirection()const { return direction_; }
	Vector2Df GetLastDirection()const { return lastDirection_; }
private:
	Vector2Df direction_;	//	入力方向
	Vector2Df lastDirection_ = {1,0};
public:
	Flag isMove_ = Flag::Off;	//	入力されているかどうか
	Flag canInput_ = Flag::On;	//	入力可能フラグ
};
