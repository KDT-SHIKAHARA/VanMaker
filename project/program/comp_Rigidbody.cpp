#include "comp_Rigidbody.h"
#include "Time.h"
#include "GameObject.h"
#include "system_rigidbody.h"

#include<algorithm>

/// <summary>
/// 外力を加える
/// </summary>
/// <param name="force"></param>
void Rigidbody::AddForce(const Vector2Df& force)
{
    if (!enableMovement_) return;
    acceleration_ += Vector2Df(force.x / mass_, force.y / mass_);

    // 加速度上限
    acceleration_.x = std::clamp(acceleration_.x, -maxAcceleration_.x, maxAcceleration_.x);
    acceleration_.y = std::clamp(acceleration_.y, -maxAcceleration_.y, maxAcceleration_.y);

}

/// <summary>
/// システムに追加
/// </summary>
void Rigidbody::Initialize()
{
	RigidbodySystem::Instance().RegisterRigidbody(this);
}

/// <summary>
/// 重力を加え、移動量を更新する
/// </summary>
void Rigidbody::Update()
{
    //  移動可能フラグ
	if (!enableMovement_) return;

	//  重力有効状態で、地面に設置されていない場合
    if(enableGravity_ && !isGraunded_){
		//  重力を加える
        acceleration_.y += gravity_;
	}

	//  移動量の更新
    velocity_ += acceleration_ * static_cast<float>(Time::deltaTime());

    //  速度上限
	velocity_.x = std::clamp(velocity_.x, -maxVelocity_.x, maxVelocity_.x);
	velocity_.y = std::clamp(velocity_.y, -maxVelocity_.y, maxVelocity_.y);



}

/// <summary>
/// Rigidbodyの移動量を位置に反映する
/// </summary>
void Rigidbody::Move()
{
	if (!enableMovement_) return;

	//  実際の移動量
	Vector2Df moveVelocity = velocity_;

	//  入力による移動が可能な場合、入力分の移動量を加える
	if (canInputMove_) {
		moveVelocity += inputVelocity_;
	}
	
	//  X移動可能

	//	Y移動可能

	//	1フレ単位の移動量に変換
	moveVelocity = moveVelocity * Time::deltaTime();

	//  移動量を位置に反映
	GetGameObject()->transform_.AddPosition(moveVelocity);

}
