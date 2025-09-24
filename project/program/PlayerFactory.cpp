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
	//	�f�[�^�擾
	auto playerData = GameDataBase::Instance().GetPlayerData(id);

	//	���݂��Ȃ��ꍇ
	if (!playerData) {
		throw std::invalid_argument("PlayerFactory::CreatePlayer: Invalid player ID");
	}

	//	�C���X�^���X����
	auto player = std::make_shared<GameObject>();

	//	�R���|�[�l���g�ǉ�
	auto rigid = player->AddComponent<Rigidbody>();
	auto collider = player->AddComponent<CircleCollider>(50.f);
	player->AddComponent<Image>(playerData->layer, playerData->filePath, Image::Pivot::Center);
	player->AddComponent<InputComponent>();
	player->AddComponent<StateComponent>(playerData->speed);
	player->AddComponent<CameraFollow>();

	//	�^�O�ݒ�
	player->tag_ = GameObjectTag::Player;

    return player;
}
