#pragma once
#include"MonoBehaviour.h"
#include"GameObject.h"
#include"comp_Health.h"
#include"comp_dissappearEffect.h"
#include"GameObjectRequestAdd.h"
#include"db_Game.h"

class DissapperCreate : public MonoBehaviour {
protected:

	void create() { 
		auto data = GameDataBase::Instance().GetAnimData(animID);
		auto obj = std::make_shared<GameObject>();
		obj->transform_.SetPosition(GetGameObject()->transform_.WorldPosition());
		auto anim = obj->AddComponent<AnimationComp>(data->layer);
		anim->AddAnim(data->name, data->filePath, data->animFirstFrame, data->animLastFrame,0.08,1.0f,Anim2D::PlayMode::Ones);
		obj->AddComponent<comp_DissapperEffect>();
		GameObjectQueue::Instance().Enqueue(obj);
	}
public:
	DissapperCreate(int a_animId)
		:animID(a_animId)
	{
	}


	void Update() {
		//	‘Ì—Í
		auto hp = GetGameObject()->GetComponentAsBase<Health>();
		if (!hp) return;

		//	‘Ì—Í‚ª‚È‚­‚È‚Á‚Ä‚¢‚½‚ç
		if (hp->GetCurrentHp() <= 0) {
			create();
		}

	}
protected:
	int animID;
};