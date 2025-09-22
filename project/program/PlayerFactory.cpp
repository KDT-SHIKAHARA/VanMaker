#include "PlayerFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "Image.h"


std::shared_ptr<GameObject> PlayerFactory::CreatePlayer()
{
	//	�f�[�^�擾


	//	�C���X�^���X����
	auto player = std::make_shared<GameObject>();

	//	�R���|�[�l���g�ǉ�
	auto rigid = player->AddComponent<Rigidbody>();
	auto collider = player->AddComponent<CircleCollider>(50.f);
	player->AddComponent<Image>(1, "resources/player.png", Image::Pivot::Center);


	//	�^�O�ݒ�
	player->tag_ = GameObjectTag::Player;

    return player;
}
