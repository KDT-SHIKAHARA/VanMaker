#include "comp_ReflectionRingh.h"
#include"Time.h"
#include"flag.h"
#include"Camera.h"
#include"DxlibRap.h"
#include"random.h"
#include"GameObject.h"
#include"GetColor.h"

ReflectionRingBehaviour::ReflectionRingBehaviour(float speed, float duration, float radius)
	: speed_(speed), lifeTime_(duration), radius_(radius)
{
    // ランダムな方向に発射
    float angle = Random::RandomAngle();
    velocity_ = { std::cos(angle) * speed_, std::sin(angle) * speed_ };
}

void ReflectionRingBehaviour::Initialize()
{
    
}

void ReflectionRingBehaviour::Update()
{
    // 位置更新
    auto& pos = GetGameObject()->transform_;
    pos.AddPosition(velocity_);

    // 画面端で跳ね返る
    const auto& cam = Camera::Instance();
    auto halfW = cam.GetSize().x / 2.0f;
    auto halfH = cam.GetSize().y / 2.0f;
    auto worldPos = pos.WorldPosition();

    if (worldPos.x - radius_ < cam.GetPosition().x - halfW || worldPos.x + radius_ > cam.GetPosition().x + halfW) {
        velocity_.x = -velocity_.x;
    }
    if (worldPos.y - radius_ < cam.GetPosition().y - halfH || worldPos.y + radius_ > cam.GetPosition().y + halfH) {
        velocity_.y = -velocity_.y;
    }

    // 持続時間の減少
    if (lifeTime_ > 0) lifeTime_ -= Time::deltaTime();
    if (lifeTime_ <= 0) {
        GetGameObject()->isDestory_.Set(Flag::On);
    }
}

void ReflectionRingBehaviour::Draw()
{
    // 半透明リングの描画
    auto& pos = GetGameObject()->transform_;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200); // 半透明
    RapperDxlib::DrawCircleAACamera(pos.WorldPosition(), radius_,10, LIGHTBLUE,FALSE,6.0f);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す
}
