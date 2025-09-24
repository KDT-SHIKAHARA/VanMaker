#pragma once
#include"MonoBehaviour.h"
#include"GameObject.h"
#include"vector2d.h"
#include"comp_Rigidbody.h"

#include<memory>

/// <summary>
/// プレイヤーを追跡する敵の動作を管理するクラスです。
/// </summary>
class EnemyFollowPlayer : public MonoBehaviour {
public:
	EnemyFollowPlayer(float a_speed)
		:speed_(a_speed){ }

	void Initialize()override;
	void Update()override;

	Vector2Df GetDirection()const { return direction_; }
private:
	Vector2Df direction_;
	std::weak_ptr<GameObject> player_;
	std::weak_ptr<Rigidbody> rigidbody_;
	float speed_;
};