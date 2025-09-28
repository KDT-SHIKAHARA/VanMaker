#pragma once
#include"MonoBehaviour.h"
#include"comp_animation.h"
#include"GameObject.h"

//	消滅エフェクトをもつGameObjectの生存管理
class comp_DissapperEffect : public MonoBehaviour{
public:
	//	ポインタ取得
	void Initialize()override {
		anim_ = GetGameObject()->GetComponent<AnimationComp>();

	}

	void Update()override {
		auto anim = anim_.lock();
		//	存在判定
		if (anim) {
			//	終了判定
			if (anim->IsFinished()) {
				GetGameObject()->isDestory_.Set(Flag::On);
			}
		}
	}

protected:
	std::weak_ptr<AnimationComp> anim_;
};