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
	//	���͂����邩�ǂ����𔻒�
	if (input->isMove_) {
		//	��Ԃ��ړ�
		state_ = State::Walk;
	}
	else {
		//	��Ԃ�ҋ@
		state_ = State::Idle;
	}


	//	�A�j���[�V�����̎擾
	auto anim = GetGameObject()->GetComponent<AnimationComp>();


	//	��Ԃɂ����
	switch (state_)
	{
	case StateComponent::State::Idle:
		anim->SetAnimKey("Idle");
		break;
	case StateComponent::State::Walk:
	{
		//	�ړ��ʂ�n��
		auto rigidbody = rigidbody_.lock();
		if (!rigidbody)return;

		//	�������擾
		auto direct = input->GetDirection();
		auto move = (direct * moveSpeed_);

		//	�ړ�
		rigidbody->AddVelocity(move);



		//	�������̓��͕����ɉ����Ĕ��]�t���O��ύX����B
		if (direct.x > 0) { anim->trans_.Set(Flag::Off); }
		if (direct.x < 0) { anim->trans_.Set(Flag::On);  }

		anim->SetAnimKey("Walk");

	}
		break;
	default:
		break;
	}


}
