#include "PlayerFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "Image.h"
#include "db_Game.h"
#include "comp_state.h"
#include "comp_input.h"
#include "comp_CameraFollow.h"

#include <stdexcept>


std::shared_ptr<GameObject> PlayerFactory::CreatePlayer(int id)
{
	//	データ取得
	auto playerData = GameDataBase::Instance().GetPlayerData(id);

	//	存在しない場合
	if (!playerData) {
		throw std::invalid_argument("PlayerFactory::CreatePlayer: Invalid player ID");
	}

	//	インスタンス生成
	auto player = std::make_shared<GameObject>();

	//	コンポーネント追加
	auto rigid = player->AddComponent<Rigidbody>();
	auto collider = player->AddComponent<CircleCollider>(50.f);
	player->AddComponent<Image>(playerData->layer, playerData->filePath, Image::Pivot::Center);
	player->AddComponent<InputComponent>();
	player->AddComponent<StateComponent>(playerData->speed);
	player->AddComponent<CameraFollow>();

	//	タグ設定
	player->tag_ = GameObjectTag::Player;

    return player;
}
