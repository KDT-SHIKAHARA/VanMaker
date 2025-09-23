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
	//	“ü—Í‚ª‚ ‚é‚©‚Ç‚¤‚©‚ð”»’è
	if (input->isMove_) {
		//	ó‘Ô‚ðˆÚ“®
		state_ = State::Walk;
	}
	else {
		//	ó‘Ô‚ð‘Ò‹@
		state_ = State::Idle;
	}

	//	ó‘Ô‚É‚æ‚Á‚Ä
	switch (state_)
	{
	case StateComponent::State::Idle:

		break;
	case StateComponent::State::Walk:
	{
		//	ˆÚ“®—Ê‚ð“n‚·
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
