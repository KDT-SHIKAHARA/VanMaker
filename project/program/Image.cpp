#include "Image.h"
#include"GameObject.h"
#include"loader_Texture.h"

#include<DxLib.h>

Image::Image(int a_layer, const std::string& a_filePath , Pivot a_pivot)
	:Drawable(a_layer), Component(), pivot_(a_pivot)
{
	texture_ = TextureLoader::Instance().LoadTexture(a_filePath);
	GetGraphSizeF(texture_->GetHandle(), &size_.x, &size_.y);

}	//	constructor

void Image::Draw()
{
	if (!texture_) return;	//	nullptrチェック
	if (!texture_->HasHandle()) return;	// 	ハンドルチェック
	if (!isVisible_) return;	//	表示フラグチェック
	

	//	描画の基準点
	auto offset = Vector2Df{ 0.0f,0.0f };

	//	中心基準なら
	if(pivot_ == Pivot::Center){
		offset.x = (size_.x * scale_.x) / 2.0f;
		offset.y = (size_.y * scale_.y) / 2.0f;
	}

	//	描画位置
	auto draw = GetGameObject()->transform_.WorldPosition() - offset;

	//	描画サイズ
	auto size = size_ * scale_;

	//	描画
	DrawExtendGraphF(draw.x, draw.y, draw.x + size.x, draw.y + size.y, texture_->GetHandle(), TRUE);

} // draw
