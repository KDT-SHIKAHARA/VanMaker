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

	//	�����蔻��
	void OnCollisionEnter(const Collision& collision) {
		//	�������Ă����G�̍U���p�R���|�[�l���g
		auto attack = collision.other->GetComponent<AttackComp>();
		auto health = GetGameObject()->GetComponentAsBase<Health>();

		//	�K�v�Ȃ��̂��Ȃ���Ώ������s��Ȃ�
		if (!attack || !health) return;

		//	�̗͂����炷
		health->Damage(attack->Attack());

	}

protected:


};
