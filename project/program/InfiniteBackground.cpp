#include "InfiniteBackground.h"
#include "loader_Texture.h"
#include "data_Window.h"
#include "Camera.h"

InfiniteBackground::InfiniteBackground(const std::string& a_filePath){
	texture_ = TextureLoader::Instance().LoadTexture(a_filePath);
	bgSize_ = { (float)WindowData::m_sceneW, (float)WindowData::m_sceneH };
}

void InfiniteBackground::Update()
{
	const auto& camera = Camera::Instance().GetPosition();
}

void InfiniteBackground::Draw()
{
    const auto& camPos = Camera::Instance().GetPosition();

    // 左上基準でスクロールオフセット計算
    int offsetX = (int)(-camPos.x) % (int)bgSize_.x;
    int offsetY = (int)(-camPos.y) % (int)bgSize_.y;

    // 負のmod対策（C++の%は負数に弱い）
    if (offsetX > 0) offsetX -= (int)bgSize_.x;
    if (offsetY > 0) offsetY -= (int)bgSize_.y;

    // 4枚描画して画面を埋める
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            DrawGraph(
                offsetX + i * (int)bgSize_.x,
                offsetY + j * (int)bgSize_.y,
                texture_->GetHandle(),
                TRUE
            );
        }
    }
}
