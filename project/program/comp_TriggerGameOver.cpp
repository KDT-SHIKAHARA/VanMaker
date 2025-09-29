#include "comp_TriggerGameOver.h"
#include "GameObjectRequestAdd.h"
#include"db_Game.h"
#include"comp_dissappearEffect.h"
#include"SceneManager.h"
#include"GameOverOverLay.h"

void TriggerGameOver::createDeadAnim()
{
	//	アニメーションと生存管理
	auto data = GameDataBase::Instance().GetAnimData(animID);
	auto obj = std::make_shared<GameObject>();
	obj->transform_.SetPosition(GetGameObject()->transform_.WorldPosition());
	auto anim = obj->AddComponent<AnimationComp>(data->layer);
	anim->AddAnim(data->name, data->filePath, data->animFirstFrame, data->animLastFrame, 0.08, 1.0f, Anim2D::PlayMode::Ones);
	obj->AddComponent<comp_DissapperEffect>();

	//	参照取得
	anim_obj_ = obj;
	//	sceneのコレクションに追加
	GameObjectQueue::Instance().Enqueue(obj);
}

void TriggerGameOver::Initialize()
{
	//	終了条件用の体力コンポーネント
	hp_ = GetGameObject()->GetComponentAsBase<Health>();
}

void TriggerGameOver::Update()
{

	auto hp = hp_.lock();
	if (!hp) return;

	//	体力が０のとき
	if (hp->IsDead()) {

		//	まだ有効フラグが残っているとき
		if (!GetGameObject()->isDead_) {
			//	インスタンスの生成
			createDeadAnim();

			GetGameObject()->isDead_.Set(Flag::On);

		}

		//	参照先のインスタンスが破棄されているとき
		if (anim_obj_.expired()) {
			//	ゲームオーバーのスクリーンの生成
			SceneManager::Instance().CreateOverlay<GameOverOverlay>();
		}
	}




}
