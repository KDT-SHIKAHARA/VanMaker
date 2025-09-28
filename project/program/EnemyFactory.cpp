#include "EnemyFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "db_Game.h"
#include "comp_animation.h"
#include "comp_EnemyFollowPlayer .h"
#include "comp_Health.h"
#include "comp_DrawCollider.h"
#include "comp_Attack.h"
#include "comp_DrawableHealth.h"
#include "comp_DamageReceiver.h"
#include "Image.h"
#include"DebugMacro.h"
#include "DropExperienceComp.h"
#include"Camera.h"
#include"random.h"
#include"comp_dissapperCreate.h"

#include<stdexcept>

Vector2Df EnemyFactory::GetSpawnPosition(int margin_length)
{
	//	4方向
	int side = Random::RandomInt(0,3);
	float x, y = 0;

	const auto& camerapos = Camera::Instance().GetPosition();
	const auto& camerasize = Camera::Instance().GetSize();


	int left = camerapos.x - camerasize.x / 2.0f;
	int right = camerapos.x + camerasize.x / 2.0f;
	int top = camerapos.y - camerasize.y / 2.0f;
	int bottom = camerapos.y + camerasize.y / 2.0f;
	
	switch (side) {
	case 0: // 上
		x = Random::RandomInt(left - margin_length, right + margin_length);
		y = top - margin_length;
		break;
	case 1: // 下
		x = Random::RandomInt(left - margin_length, right + margin_length);
		y = bottom + margin_length;
		break;
	case 2: // 左
		x = left - margin_length;
		y = Random::RandomInt(top - margin_length, bottom + margin_length);
		break;
	case 3: // 右
		x = right + margin_length;
		y = Random::RandomInt(top - margin_length, bottom + margin_length);
		break;
	}
	return { x, y };
}

/// <summary>
/// 指定されたIDに基づいて敵オブジェクトを生成し、共有ポインタとして返します。
/// </summary>
/// <param name="id">生成する敵オブジェクトの識別子。</param>
/// <returns>生成された敵オブジェクトへのstd::shared_ptr。</returns>
std::shared_ptr<GameObject> EnemyFactory::CreateEnemy(int id)
{
	//	データ取得
	auto data = GameDataBase::Instance().GetEnemyData(id);
	auto anim_data = GameDataBase::Instance().GetAnimData(data->textureID);
	auto size_data = GameDataBase::Instance().GetEnemySizeData(data->sizeTypeId);

	//	インスタンス生成
	auto enemy = std::make_shared<GameObject>();

	//	移動量
	enemy->AddComponent<Rigidbody>();

	//	当たり判定
	enemy->AddComponent<RectCollider>(Vector2Df{(float)size_data->base_width * size_data->exrate,(float)size_data->base_height * size_data->exrate });

	//	アニメーション
	auto anim = enemy->AddComponent<AnimationComp>(anim_data->layer);
	anim->AddAnim(anim_data->name, anim_data->filePath, anim_data->animFirstFrame, anim_data->animLastFrame,0.2f,size_data->exrate);

	//	プレイヤーに向けて移動
	enemy->AddComponent<EnemyFollowPlayer>(1);



	if (DebugFlag::DrawCollider) {
		//	当たり判定の可視化
		enemy->AddComponent<DrawRectColliderComp>();
	}

	if (DebugFlag::EnemyDrawHpBar) {
		auto hp = enemy->AddComponent<DrawableHealth>(0, data->hp, anim_data->layer + 2, Vector2Df{ 70,10 });
		hp->SetOffset(Vector2Df{ 0,40 });

	}
	else {
		//	体力
		enemy->AddComponent<Health>(1.0, data->hp);
	}
	
	//	攻撃
	enemy->AddComponent<AttackComp>(data->attack, data->coolTime_,data->id);

	//	被弾用
	enemy->AddComponent<DamageReceiver>();

	//	経験値
	enemy->AddComponent<DropExperienceComp>(data->dropExpId);

	//	出現パターンを後から追加して。
	enemy->transform_.SetPosition(GetSpawnPosition(50.f));

	enemy->AddComponent<DissapperCreate>(data->dissAnimId);

	//	タグ
	enemy->tag_ = GameObjectTag::Enemy;
	return enemy;
}
