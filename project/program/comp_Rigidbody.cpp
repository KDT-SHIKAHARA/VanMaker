#include "comp_Rigidbody.h"
#include "Time.h"
#include "GameObject.h"
#include "system_rigidbody.h"

#include<algorithm>

/// <summary>
/// �O�͂�������
/// </summary>
/// <param name="force"></param>
void Rigidbody::AddForce(const Vector2Df& force)
{
    if (!enableMovement_) return;
    acceleration_ += Vector2Df(force.x / mass_, force.y / mass_);

    // �����x���
    acceleration_.x = std::clamp(acceleration_.x, -maxAcceleration_.x, maxAcceleration_.x);
    acceleration_.y = std::clamp(acceleration_.y, -maxAcceleration_.y, maxAcceleration_.y);

}

/// <summary>
/// �V�X�e���ɒǉ�
/// </summary>
void Rigidbody::Initialize()
{
	RigidbodySystem::Instance().RegisterRigidbody(this);
}

/// <summary>
/// �d�͂������A�ړ��ʂ��X�V����
/// </summary>
void Rigidbody::Update()
{
    //  �ړ��\�t���O
	if (!enableMovement_) return;

	//  �d�͗L����ԂŁA�n�ʂɐݒu����Ă��Ȃ��ꍇ
    if(enableGravity_ && !isGraunded_){
		//  �d�͂�������
        acceleration_.y += gravity_;
	}

	//  �ړ��ʂ̍X�V
    velocity_ += acceleration_ * static_cast<float>(Time::deltaTime());

    //  ���x���
	velocity_.x = std::clamp(velocity_.x, -maxVelocity_.x, maxVelocity_.x);
	velocity_.y = std::clamp(velocity_.y, -maxVelocity_.y, maxVelocity_.y);



}

/// <summary>
/// Rigidbody�̈ړ��ʂ��ʒu�ɔ��f����
/// </summary>
void Rigidbody::Move()
{
	if (!enableMovement_) return;

	//  ���ۂ̈ړ���
	Vector2Df moveVelocity = velocity_;

	//  ���͂ɂ��ړ����\�ȏꍇ�A���͕��̈ړ��ʂ�������
	if (canInputMove_) {
		moveVelocity += inputVelocity_;
	}
	
	//  X�ړ��\

	//	Y�ړ��\

	//	1�t���P�ʂ̈ړ��ʂɕϊ�
	moveVelocity = moveVelocity * Time::deltaTime();

	//  �ړ��ʂ��ʒu�ɔ��f
	GetGameObject()->transform_.AddPosition(moveVelocity);

}
