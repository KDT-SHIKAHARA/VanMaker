#include "DamageFieldBehavior.h"
#include "GameObjectManager.h"
#include "GameObjectTag.h"
#include "comp_image.h"

void DamagerFieldBehaviour::Update()
{
	//	プレイヤーの座標を取得
	auto player = GameObjectRegistry::Instance().FindGameObjectsByTag(GameObjectTag::Player);

	//	自身の座標をプレイヤーと同じ座標にする
	GetGameObject()->transform_.SetPosition(player[0]->transform_.WorldPosition());

	auto image = GetGameObject()->GetComponent<ImageComponent>();
	if (image) {
		image->AddAngle(angle_speed_);
	}


}
