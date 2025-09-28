#include "Behaviour_Thunderbolt.h"
#include "Time.h"
#include "GameObject.h"
#include "DxlibRap.h"
#include "GetColor.h"
#include "Camera.h"

void ThunderboltBehaviour::Initialize()
{

}

void ThunderboltBehaviour::Update()
{
	//	時間を減らす
	if (lifeTime_ > 0) {
		lifeTime_ -= Time::deltaTime();
	}

	//	時間がなくなったらインスタンスの削除
	if (lifeTime_ <= 0) {
		//	削除フラグを立てる
		GetGameObject()->isDestory_.Set(Flag::On);
	}
}

void ThunderboltBehaviour::Draw()
{
	float worldTopY = Camera::Instance().GetPosition().y - Camera::Instance().GetSize().y / 2.0f;
	auto pos =  Vector2Df{ targetPos_.x,worldTopY };
	RapperDxlib::DrawLightning(pos, targetPos_,10,10.f,BLUE,2.0f);
}
