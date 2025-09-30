#include "comp_KnifeWeapon.h"
#include "GameObject.h"
#include "Camera.h"
#include "Collision.h"

//	ˆÚ“®ƒxƒNƒgƒ‹
KnifeBehaviour::KnifeBehaviour(const Vector2Df& a_duration, float a_speed)
	:OutScene_(false)
{
	velocity_ = a_duration * a_speed;
}

void KnifeBehaviour::Update()
{
	//	‰ÁŽZ
	GetGameObject()->transform_.AddPosition(velocity_);

	//	‰æ–Ê“à”»’è
	OutScene_ = !Camera::Instance().Contains(GetGameObject()->transform_.WorldPosition());

	//	íœ
	if (OutScene_) {
		GetGameObject()->isDestory_.Set(Flag::On);
	}
}

void KnifeBehaviour::OnCollisionEnter(const Collision& collision)
{
	if (collision.other->tag_ == GameObjectTag::Enemy) {
		GetGameObject()->isDestory_.Set(Flag::On);
	}
}
