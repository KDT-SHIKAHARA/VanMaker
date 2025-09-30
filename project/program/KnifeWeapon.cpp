#include "KnifeWeapon.h"

#include"db_Game.h"
#include"GameObjectManager.h"
#include"GameObjectRequestAdd.h"
#include"comp_input.h"
#include"comp_Attack.h"


void KnifeWeapon::create()
{
	//	データID
	auto id = 304000;

	//	データの取得
	const auto& data = GameDataBase::Instance().GetWeaponData(id);
	const auto& level_data = GameDataBase::Instance().GetWeaponLevelData(id, level_);

	//	今のレベルのクールタイム
	max_ct_ = level_data->cooltime;

	//	プレイヤーの座標取得
	auto player = GameObjectRegistry::Instance().FindGameObjectsByTag(GameObjectTag::Player);
	const auto& playerPos = player[0]->transform_.WorldPosition();

	//	プレイヤーの移動方向を取得
	const auto& duration = player[0]->GetComponent<InputComponent>()->GetDirection();

	//	個数分インスタンスの生成
	for (size_t i = 0; i < level_data->create_num; i++) {
		auto obj = std::make_shared<GameObject>();
		obj->transform_.SetPosition(playerPos);
		obj->AddComponent<AttackComp>(level_data->attack, data->slip_ct, id);
		//	挙動
		obj->tag_ = GameObjectTag::Weapon;
		GameObjectQueue::Instance().Enqueue(obj);
	}
}

void KnifeWeapon::Initialize()
{
	//	データID
	auto id = 304000;
	//	データの取得
	const auto& data = GameDataBase::Instance().GetWeaponData(id);

	//	初期化
	name_ = data->name;
	max_level_ = data->max_level;

}

void KnifeWeapon::Update()
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
