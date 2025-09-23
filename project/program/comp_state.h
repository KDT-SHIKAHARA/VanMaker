#pragma once
#include"Component.h"
#include"MonoBehaviour.h"
#include"flag.h"
#include "comp_input.h"
#include "comp_Rigidbody.h"


class StateComponent : public MonoBehaviour {
public:
	StateComponent(float a_moveSpeed);
	virtual ~StateComponent() = default;

	enum class State {
		Idle,
		Walk,
	};

	void Initialize() override;
	void Update() override;

private:
	State state_ = State::Idle;	//	���
	std::weak_ptr<InputComponent> input_;	//	���̓N���X�̈ړ���
	std::weak_ptr<Rigidbody> rigidbody_;	//	�ړ���
	float moveSpeed_ = 100.0f;	//	�ړ����x
public:
	Flag isTrans_;	//	���͂ɉ����Ĕ��]�t���O

};