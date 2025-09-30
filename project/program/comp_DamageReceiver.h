#pragma once
#include"MonoBehaviour.h"
#include"comp_Health.h"
#include"Collision.h"
#include"GameObject.h"
#include"comp_Attack.h"
#include"Time.h"

#include"filePath.h"
#include"system_EventBus.h"
#include"BGMSystem.h"

class DamageReceiver : public MonoBehaviour {
public:
	void Update()override {
		for (auto& [id, ct] : hitTimer_) {
			//	クールタイムが存在していたら減少させる
			if (ct > 0) ct -= Time::deltaTime();
		}
	}

	//	当たり判定
	void OnCollisionEnter(const Collision& collision) {
		//	当たってきた敵の攻撃用コンポーネント
		auto attack = collision.other->GetComponent<AttackComp>();
		auto health = GetGameObject()->GetComponentAsBase<Health>();

		//	必要なものがなければ処理を行わない
		if (!attack || !health) return;

		//	クールタイム中はダメージ処理を行わない
		if (hitTimer_[attack->GetID()] > 0) return;

		//	IDとクールタイムの設定
		hitTimer_[attack->GetID()] = attack->GetCT();

		//	体力を減らす
		health->Damage(attack->Attack());

		EventBus::Instance().Publish(PlayBGMEvent{ SH_FilePath::hit_se,1,6 });


	}

protected:
	//	当たってきた対象ごとのCT
	std::unordered_map<int, double> hitTimer_;

};
