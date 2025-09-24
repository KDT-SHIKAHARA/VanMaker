#include "comp_EnemyFollowPlayer .h"
#include "GameObjectManager.h"
#include "GameObjectTag.h"

void EnemyFollowPlayer::Initialize()
{
	auto list_player = GameObjectRegistry::Instance().FindGameObjectsByTag(GameObjectTag::Player);
	if (!list_player.empty()) {
		player_ = list_player[0];
	}

	rigidbody_ = GetGameObject()->GetComponent<Rigidbody>();

}

void EnemyFollowPlayer::Update()
{
	//	�Q�Ƃ����݂��Ă��邩�ǂ���
	auto player = player_.lock();
	if (!player)return;
	if (rigidbody_.expired()) return;

	//	���W
	const auto& player_pos = player->transform_.WorldPosition();
	const auto& enemy_pos = GetGameObject()->transform_.WorldPosition();

	//	���W�Ɍ������Ă̕����̍쐬
	direction_ = SetTarget(enemy_pos, player_pos);
	auto move = direction_ * speed_;
	rigidbody_.lock()->AddVelocity(move);

}
