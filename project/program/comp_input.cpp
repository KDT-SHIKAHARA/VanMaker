#include "comp_input.h"
#include "InputManager.h"
#include"GameObject.h"

#include<DxLib.h>
#include<stdexcept>


void InputComponent::Update()
{
	if (GetGameObject()->isDead_) return;

	//	クリア
	direction_.Clear();
	isMove_ = Flag::Off;

	//	入力に応じて移動方向を加算
	//	左
	if (Input::IsKeyPressed(KEY_INPUT_A)) {
		direction_ += Vector2Df{ -1,0 };
		isMove_ = Flag::On;
	}
	//	右
	if (Input::IsKeyPressed(KEY_INPUT_D)) {
		direction_ += Vector2Df{ 1,0 };
		isMove_ = Flag::On;
	}
	//	上
	if (Input::IsKeyPressed(KEY_INPUT_W)) {
		direction_ += Vector2Df{ 0,-1 };
		isMove_ = Flag::On;
	}
	//	下
	if (Input::IsKeyPressed(KEY_INPUT_S)) {
		direction_ += Vector2Df{ 0,1 };
		isMove_ = Flag::On;
	}


	//	入力が合ったら最後の入力方向の更新
	if (direction_.x != 0 || direction_.y != 0) {
		lastDirection_ = direction_;
	}

}