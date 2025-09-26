#pragma once
#include"MonoBehaviour.h"
#include"comp_Health.h"
#include"Collision.h"
#include"GameObject.h"
#include"comp_Attack.h"

class DamageReceiver : public MonoBehaviour {
public:
	void Update()override {

	}

	//	当たり判定
	void OnCollisionEnter(const Collision& collision) {
		//	当たってきた敵の攻撃用コンポーネント
		auto attack = collision.other->GetComponent<AttackComp>();
		auto health = GetGameObject()->GetComponentAsBase<Health>();

		//	必要なものがなければ処理を行わない
		if (!attack || !health) return;

		//	体力を減らす
		health->Damage(attack->Attack());

	}

protected:


};
