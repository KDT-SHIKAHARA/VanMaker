#include "comp_image.h"
#include"DxlibRap.h"
#include"GameObject.h"
#include"loader_Texture.h"


ImageComponent::ImageComponent(const std::string& filePath, float a_exRate, int a_layer, ImageComponent::Pivot a_pivot)
	:Drawable(a_layer), exRate_(a_exRate), pivot_(a_pivot),angle_(0)
	, isTurn_(Flag::Off), isTrans_(Flag::On)
{
	//	�e�N�X�`���Ǎ�
	texture_ = TextureLoader::Instance().LoadTexture(filePath);



}


void ImageComponent::Update()
{

}

void ImageComponent::Draw()
{
	//	���W�擾
	const auto& pos = GetGameObject()->transform_.WorldPosition();

	auto offset = Vector2Df{ 0,0 };

	if (pivot_ == Pivot::TopLeft) {
		offset = (size_ * exRate_) / 2.f;
	}

	//	�`�悷����W
	auto draw = pos - offset;

	//	�\��
	RapperDxlib::DrawRotaGraphFCamera(draw, exRate_, angle_, texture_->GetHandle(), isTrans_, isTurn_);
}
