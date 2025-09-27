#include "DamageField.h"
#include "GameObjectManager.h"
#include "GameObjectTag.h"
#include "comp_Collider.h"
#include "comp_Rigidbody.h"
#include "comp_DrawCollider.h"
#include "DamageFieldBehavior.h"
#include "comp_Attack.h"
#include "db_Game.h"
#include "time.h"
#include "GameObjectRequestAdd.h"
#include "comp_image.h"
#include"DebugMacro.h"

DamageField::DamageField()
{
	create();
}

void DamageField::Initialize()
{
	
}

void DamageField::Fire()
{
}

//	クールタイムの減少
void DamageField::Update()
{
	if (current_ct_ > 0) {
		current_ct_ -= Time::deltaTime();
	}

}


void DamageField::create()
{

	//	番号からデータ取得
	auto data = GameDataBase::Instance().GetWeaponData(1001);
	auto image_data = GameDataBase::Instance().GetImageData(data->textureID);

	//	個数分メモリ領域を取得しておく
	for (size_t i = 0; i < data->num; i++) {
		//	インスタンスの生成
		auto obj = std::make_shared<GameObject>();

		//	コンポーネントの追加

		
		//	当たり判定
		obj->AddComponent<CircleCollider>(data->radius);
		if (DebugFlag::DrawCollider) {
			//	当たり判定の可視化
			obj->AddComponent<DrawCircleColliderComp>();
		}
		//	挙動
		obj->AddComponent<DamagerFieldBehaviour>();

		//	攻撃
		obj->AddComponent<AttackComp>(data->attack, data->slip_ct);

		//	表示
		obj->AddComponent<ImageComponent>(image_data->filePath, image_data->exRate, image_data->layer);

		//	タグの設定
		obj->tag_ = GameObjectTag::Weapon;

		//	追加リストに追加
		GameObjectQueue::Instance().Enqueue(obj);
	}


}