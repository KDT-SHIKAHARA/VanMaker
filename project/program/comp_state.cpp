#include "comp_state.h"
#include "GameObject.h"
#include "comp_animation.h"

#include<stdexcept>


StateComponent::StateComponent(float a_moveSpeed)
	:moveSpeed_(a_moveSpeed)
{

}

void StateComponent::Initialize()
{
	input_ = GetGameObject()->GetComponent<InputComponent>();
	rigidbody_ = GetGameObject()->GetComponent<Rigidbody>();
}

void StateComponent::Update()
{
	auto input = input_.lock();
	//	入力があるかどうかを判定
	if (input->isMove_) {
		//	状態を移動
		state_ = State::Walk;
	}
	else {
		//	状態を待機
		state_ = State::Idle;
	}


	//	アニメーションの取得
	auto anim = GetGameObject()->GetComponent<AnimationComp>();


	//	状態によって
	switch (state_)
	{
	case StateComponent::State::Idle:
		anim->SetAnimKey("Idle");
		break;
	case StateComponent::State::Walk:
	{
		//	移動量を渡す
		auto rigidbody = rigidbody_.lock();
		if (!rigidbody)return;

		//	方向を取得
		auto direct = input->GetDirection();
		auto move = (direct * moveSpeed_);

		//	移動
		rigidbody->AddVelocity(move);



		//	横方向の入力方向に応じて反転フラグを変更する。
		if (direct.x > 0) { anim->trans_.Set(Flag::Off); }
		if (direct.x < 0) { anim->trans_.Set(Flag::On);  }

		anim->SetAnimKey("Walk");

	}
		break;
	default:
		break;
	}


}
