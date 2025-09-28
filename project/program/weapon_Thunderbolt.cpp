#include "weapon_Thunderbolt.h"
#include "db_Game.h"
#include "GameObject.h"
#include "comp_Collider.h"
#include "comp_Attack.h"
#include "GameObjectRequestAdd.h"
#include "comp_DrawCollider.h"
#include "DebugMacro.h"
#include"Time.h"
#include"Behaviour_Thunderbolt.h"
#include"Camera.h"

void Thunderbolt::create()
{
	//	データ読み込み
	auto id = 3002;
	auto data = GameDataBase::Instance().GetWeaponData(id);

	//	クールタイムの設定
	max_ct_ = data->max_ct;
	
	//	データの取得
	auto targetPos = Camera::Instance().GetObjectsInCameraWithTag(GameObjectTag::Enemy, data->num);

	//	本数分生成する
	for (size_t i = 0; i < targetPos.size(); i++) {
		//	オブジェクトインスタンス
		auto obj = std::make_shared<GameObject>();

		//	座標をセット
		obj->transform_.SetPosition(targetPos[i]->transform_.WorldPosition());

		//	当たり判定
		obj->AddComponent<CircleCollider>(data->radius);

		if (DebugFlag::DrawCollider) {
			obj->AddComponent<DrawCircleColliderComp>();
		}

		//	攻撃
		obj->AddComponent<AttackComp>(data->attack, data->slip_ct, id);

		//	挙動
		obj->AddComponent<ThunderboltBehaviour>(
			obj->transform_.WorldPosition(), data->slip_ct,data->textureID);

		//	タグの設定
		obj->tag_ = GameObjectTag::Weapon;

		//obj->enable_.Set(Flag::On);

		//	インスタンスの追加
		GameObjectQueue::Instance().Enqueue(obj);
	}

}

Thunderbolt::Thunderbolt()
{

}

void Thunderbolt::Initialize()
{
}

void Thunderbolt::Fire()
{
}

void Thunderbolt::Update()
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
