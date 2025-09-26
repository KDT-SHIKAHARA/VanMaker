#include "EnemyFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "db_Game.h"
#include "comp_animation.h"
#include "comp_EnemyFollowPlayer .h"
#include "comp_Health.h"
#include "comp_DrawCollider.h"

#include<stdexcept>

/// <summary>
/// 指定されたIDに基づいて敵オブジェクトを生成し、共有ポインタとして返します。
/// </summary>
/// <param name="id">生成する敵オブジェクトの識別子。</param>
/// <returns>生成された敵オブジェクトへのstd::shared_ptr。</returns>
std::shared_ptr<GameObject> EnemyFactory::CreateEnemy(int id, int anim_id)
{
	//	データ取得
	auto data = GameDataBase::Instance().GetEnemyData(id);
	auto anim_data = GameDataBase::Instance().GetAnimData(anim_id);
	auto size_data = GameDataBase::Instance().GetEnemySizeData(data->sizeTypeId);

	//	インスタンス生成
	auto enemy = std::make_shared<GameObject>();

	//	移動量
	enemy->AddComponent<Rigidbody>();

	//	当たり判定
	enemy->AddComponent<RectCollider>(Vector2Df{(float)size_data->base_width,(float)size_data->base_height });

	//	アニメーション
	auto anim = enemy->AddComponent<AnimationComp>(anim_data->layer);
	anim->AddAnim(anim_data->name, anim_data->filePath, anim_data->animFirstFrame, anim_data->animLastFrame,0.2f,size_data->exrate);

	//	プレイヤーに向けて移動
	enemy->AddComponent<EnemyFollowPlayer>(1);


	//	当たり判定の可視化
	enemy->AddComponent<DrawRectColliderComp>();



	//	体力
	auto hp = enemy->AddComponent<Health>(1.0, data->hp);

	//	タグ
	enemy->tag_ = GameObjectTag::Enemy;
	return enemy;
}
