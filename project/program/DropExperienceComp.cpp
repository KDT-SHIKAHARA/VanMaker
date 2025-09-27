#include "DropExperienceComp.h"
#include "GameObject.h"
#include "GameObjectRequestAdd.h"
#include "db_Game.h"
#include "comp_Collider.h"
#include "comp_DrawCollider.h"
#include "DebugMacro.h"
#include "comp_image.h"

//	インスタンスの生成をして追加する
void DropExperienceComp::create()
{
	//	データの取得
	auto data = GameDataBase::Instance().GetDropExpData(id_);
	auto texture = GameDataBase::Instance().GetImageData(data->texture_id);

	//	インスタンスの生成
	auto obj = std::make_shared<GameObject>();

	//	座標設定
	const auto& pos = GetGameObject()->transform_.WorldPosition();
	obj->transform_.SetPosition(pos);

	//	当たり判定
	obj->AddComponent<RectCollider>(Vector2Df{ data->width,data->height });

	//	当たり判定の可視化
	if (DebugFlag::DrawCollider) {
		obj->AddComponent<DrawRectColliderComp>(texture->layer + 1);
	}

	//	表示
	obj->AddComponent<ImageComponent>(texture->filePath, texture->exRate, texture->layer);

	//	コレクションに追加
	GameObjectQueue::Instance().Enqueue(obj);
}

DropExperienceComp::DropExperienceComp(int id)
	:id_(id)
{

}

void DropExperienceComp::Initialize()
{
	hp_ = GetGameObject()->GetComponentAsBase<Health>();
}

void DropExperienceComp::Update()
{
	//	参照確認
	auto hp = hp_.lock();
	if (!hp) return;

	//	生存判定
	if (!hp->alive_) {
		//	まだドロップしていなかったら
		if (!dropped_) {
			//	生成をする
			create();
			//	生成済みにする
			dropped_ = true;
		}
	}
}
