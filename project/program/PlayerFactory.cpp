#include "PlayerFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "Image.h"
#include "db_Game.h"
#include "comp_state.h"
#include "comp_input.h"
#include "comp_CameraFollow.h"
#include "comp_DrawableHealth.h"
#include "comp_animation.h"
#include "comp_DrawCollider.h"
#include "comp_DamageReceiver.h"

#include <stdexcept>


std::shared_ptr<GameObject> PlayerFactory::CreatePlayer(int id)
{
	//	データ取得
	auto data = GameDataBase::Instance().GetPlayerData(id);
	auto idle_anim = GameDataBase::Instance().GetAnimData(1001);
	auto walk_anim = GameDataBase::Instance().GetAnimData(1002);

	//	存在しない場合
	if (!data) {
		throw std::invalid_argument("PlayerFactory::CreatePlayer: Invalid player ID");
	}

	//	インスタンス生成
	auto player = std::make_shared<GameObject>();

	//	移動量
	auto rigid = player->AddComponent<Rigidbody>();

	//	当たり判定
	auto collider = player->AddComponent<RectCollider>(Vector2Df{ data->size_w_,data->size_h_ });

	//	デバック中だけ
#ifdef _DEBUG
	player->AddComponent<DrawRectColliderComp>();
#endif // _DEBUG


	//	入力
	player->AddComponent<InputComponent>();

	//	状態
	player->AddComponent<StateComponent>(data->speed);

	//	カメラの追従用
	player->AddComponent<CameraFollow>();

	//	アニメーション
	auto anim = player->AddComponent<AnimationComp>(walk_anim->layer);
	anim->AddAnim(walk_anim->name, walk_anim->filePath, walk_anim->animFirstFrame, walk_anim->animLastFrame,0.15f);
	anim->AddAnim(idle_anim->name, idle_anim->filePath, idle_anim->animFirstFrame, idle_anim->animLastFrame);
	anim->SetExRate(1.2);

	//	体力
	auto hp = player->AddComponent<DrawableHealth>(data->max_invi, data->hp, walk_anim->layer + 1, Vector2Df{ 70,10 });
	hp->SetOffset(Vector2Df{0,40});

	//	被弾用
	player->AddComponent<DamageReceiver>();


	//	タグ設定
	player->tag_ = GameObjectTag::Player;

    return player;
}
