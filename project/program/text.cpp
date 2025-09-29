#include "text.h"
#include "vector2d.h"
#include "GameObject.h"

#include<DxLib.h>

Text::Text(const std::string& text, unsigned int color, bool center, int size, int layer)
	:Drawable(layer),text_(text), color_(color), center_(center), size_(size)
{
	fontHandle_ = CreateFontToHandle(nullptr, size_, -1, DX_FONTTYPE_ANTIALIASING);
}

void Text::Draw()
{
	if(fontHandle_ == -1) return;	//	フォントハンドルチェック
	if (!isVisible_) return;	//	表示フラグチェック

	//	描画の基準点
	auto offset = Vector2Df{ 0.0f,0.0f };

	//	中心基準なら
    // 描画座標
    auto pos = GetGameObject()->transform_.WorldPosition();

    // 描画オフセット（中心基準対応）
    if (center_) {
        int w, h = 0;
        // 文字列の幅と高さを取得
        GetDrawStringSizeToHandle(&w, &h, nullptr, text_.c_str(), -1, fontHandle_);

        pos.x -= w / 2.0f;
        pos.y -= h / 2.0f;
    }

    // 描画
    DrawStringToHandle(static_cast<int>(pos.x), static_cast<int>(pos.y), text_.c_str(), color_, fontHandle_);
}
