#include "comp_state.h"
#include "GameObject.h"

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
	//	���͂����邩�ǂ����𔻒�
	if (input->isMove_) {
		//	��Ԃ��ړ�
		state_ = State::Walk;
	}
	else {
		//	��Ԃ�ҋ@
		state_ = State::Idle;
	}

	//	��Ԃɂ����
	switch (state_)
	{
	case StateComponent::State::Idle:

		break;
	case StateComponent::State::Walk:
	{
		//	�ړ��ʂ�n��
		auto rigidbody = rigidbody_.lock();
		if (!rigidbody)return;
		auto move = (input->GetDirection() * moveSpeed_);

		rigidbody->AddVelocity(move);
	}
		break;
	default:
		break;
	}


}
