#include "ReflectionRing.h"
#include"db_Game.h"
#include"GameObjectRequestAdd.h"
#include"GameObjectManager.h"
#include"Time.h"
#include"comp_Attack.h"
#include"comp_Collider.h"
#include"comp_ReflectionRingh.h"

void ReflectionRing::create()
{
	//	データの読み込み
	auto id = 303000;
	auto data = GameDataBase::Instance().GetWeaponData(id);
	auto levelData = GameDataBase::Instance().GetWeaponLevelData(id, level_);

	//	名前
	name_ = data->name;

	//	最大レベル
	max_level_ = data->max_level;

	//	生成のクールタイム
	max_ct_ = levelData->cooltime;

	//	有効時間の取得
	auto enable_time = levelData->duration;

	//	開始時の座標取得
	auto player = GameObjectRegistry::Instance().FindGameObjectsByTag(GameObjectTag::Player);
	const auto& playerPos = player[0]->transform_.WorldPosition();

	//	半径
	const auto& radius = data->radius;

	//	本数分生成
	for (size_t i = 0; i < levelData->create_num; i++) {
		//	obj
		auto obj = std::make_shared<GameObject>();

		//	座標セット
		obj->transform_.SetPosition(playerPos);

		//	当たり判定の追加
		obj->AddComponent<CircleCollider>(radius);

		//	攻撃
		obj->AddComponent<AttackComp>(levelData->attack, data->slip_ct, id);

		//	挙動
		obj->AddComponent<ReflectionRingBehaviour>(levelData->speed, levelData->duration, radius);

		// タグ
		obj->tag_ = GameObjectTag::Weapon;

		//	インスタンスの追加
		GameObjectQueue::Instance().Enqueue(obj);

	}

}

void ReflectionRing::Initialize()
{
}

void ReflectionRing::Update()
{
	//	時間の経過
	//	クールタイムがある時
	if (current_ct_ > 0) {
		//	時間を減らす
		current_ct_ -= Time::deltaTime();
	}

	//	クールタイムが経過していたら
	if (current_ct_ <= 0) {
		//	生成メソッドを呼び出す
		create();
		//	クールタイムの設定
		current_ct_ = max_ct_;
	}
}
