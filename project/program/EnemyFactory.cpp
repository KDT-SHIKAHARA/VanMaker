#include "EnemyFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "db_Game.h"
#include "comp_animation.h"
#include "comp_EnemyFollowPlayer .h"

#include<stdexcept>

/// <summary>
/// 指定されたIDに基づいて敵オブジェクトを生成し、共有ポインタとして返します。
/// </summary>
/// <param name="id">生成する敵オブジェクトの識別子。</param>
/// <returns>生成された敵オブジェクトへのstd::shared_ptr。</returns>
std::shared_ptr<GameObject> EnemyFactory::CreateEnemy(int id)
{
	//	データ取得
	auto data = GameDataBase::Instance().GetEnemyData(id);

	//	インスタンス生成
	auto enemy = std::make_shared<GameObject>();
	enemy->AddComponent<Rigidbody>();


	auto anim = enemy->AddComponent<AnimationComp>(1);
	anim->AddAnim("Idle", data->texturePath, data->animFirstFrame, data->animLastFrame);
	enemy->AddComponent<EnemyFollowPlayer>(1);

	return enemy;
}
