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
	State state_ = State::Idle;	//	状態
	std::weak_ptr<InputComponent> input_;	//	入力クラスの移動量
	std::weak_ptr<Rigidbody> rigidbody_;	//	移動量
	float moveSpeed_ = 100.0f;	//	移動速度
public:
	Flag isTrans_;	//	入力に応じて反転フラグ

};