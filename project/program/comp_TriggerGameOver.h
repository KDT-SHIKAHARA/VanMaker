#pragma once
#include"MonoBehaviour.h"
#include"comp_Health.h"

//	アニメーションの再生が終わったらインスタンス消去をするから
//	プレイヤーが死んだ状態(参照先の生成済み)の状態で参照先のアニメーションが存在していなかったらゲームオーバーのスクリーンを生成する。



class TriggerGameOver : public MonoBehaviour {

	void createDeadAnim();
public:
	TriggerGameOver(int a_animID = 7201)
		:animID(a_animID){ }
	void Initialize()override;
	void Update()override;

protected:
	std::weak_ptr<Health> hp_;
	std::weak_ptr<class GameObject> anim_obj_;
	int animID;
	
};