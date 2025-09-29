#include "Rect.h"
#include "GameObject.h"

void Rect::Draw()
{
    // スクリーン座標（中心基準）
    auto pos = GetGameObject()->transform_.WorldPosition();

    int left = static_cast<int>(pos.x - size_.x / 2);
    int top = static_cast<int>(pos.y - size_.y / 2);
    int right = static_cast<int>(pos.x + size_.x / 2);
    int bottom = static_cast<int>(pos.y + size_.y / 2);

    // 透過
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
    DrawBox(left, top, right, bottom, color_, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
