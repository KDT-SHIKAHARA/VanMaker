#include "PlayerFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "Image.h"


std::shared_ptr<GameObject> PlayerFactory::CreatePlayer()
{
	//	データ取得


	//	インスタンス生成
	auto player = std::make_shared<GameObject>();

	//	コンポーネント追加
	auto rigid = player->AddComponent<Rigidbody>();
	auto collider = player->AddComponent<CircleCollider>(50.f);
	player->AddComponent<Image>(1, "resources/player.png", Image::Pivot::Center);


	//	タグ設定
	player->tag_ = GameObjectTag::Player;

    return player;
}
