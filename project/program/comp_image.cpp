#include "comp_image.h"
#include"DxlibRap.h"
#include"GameObject.h"
#include"loader_Texture.h"


ImageComponent::ImageComponent(const std::string& filePath, float a_exRate, int a_layer, ImageComponent::Pivot a_pivot, RenderSpace a_renderSpace)
	:Drawable(a_layer), exRate_(a_exRate), pivot_(a_pivot),angle_(0)
	, isTurn_(Flag::Off), isTrans_(Flag::On), renderSpace_(a_renderSpace)
{
	//	テクスチャ読込
	texture_ = TextureLoader::Instance().LoadTexture(filePath);

	//	サイズ取得
	GetGraphSizeF(texture_->GetHandle(), &size_.x, &size_.y);
}


void ImageComponent::Update()
{

}

void ImageComponent::Draw()
{
	//	座標取得
	const auto& pos = GetGameObject()->transform_.WorldPosition();

	auto offset = Vector2Df{ 0,0 };

	if (pivot_ == Pivot::TopLeft) {
		offset = (size_ * exRate_) / 2.f;
	}

	//	描画する座標
	auto draw = pos + offset;

	switch (renderSpace_)
	{
	case ImageComponent::RenderSpace::World:
		//	表示
		RapperDxlib::DrawRotaGraphFCamera(draw, exRate_, angle_, texture_->GetHandle(), isTrans_, isTurn_);
		break;
	case ImageComponent::RenderSpace::Screen:
		DrawRotaGraphF(draw.x, draw.y, exRate_, angle_, texture_->GetHandle(), isTrans_, isTurn_);
		break;
	default:
		break;
	}

}
