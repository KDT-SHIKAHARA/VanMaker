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
	//	ŽQÆ‚ª‘¶Ý‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
	auto player = player_.lock();
	if (!player)return;
	if (rigidbody_.expired()) return;

	//	À•W
	const auto& player_pos = player->transform_.WorldPosition();
	const auto& enemy_pos = GetGameObject()->transform_.WorldPosition();

	//	À•W‚ÉŒü‚©‚Á‚Ä‚Ì•ûŒü‚Ìì¬
	direction_ = SetTarget(enemy_pos, player_pos);
	auto move = direction_ * speed_;
	rigidbody_.lock()->AddVelocity(move);

}
