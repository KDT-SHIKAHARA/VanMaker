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
	if (!texture_) return;	//	nullptr�`�F�b�N
	if (!texture_->HasHandle()) return;	// 	�n���h���`�F�b�N
	if (!isVisible_) return;	//	�\���t���O�`�F�b�N
	

	//	�`��̊�_
	auto offset = Vector2Df{ 0.0f,0.0f };

	//	���S��Ȃ�
	if(pivot_ == Pivot::Center){
		offset.x = (size_.x * scale_.x) / 2.0f;
		offset.y = (size_.y * scale_.y) / 2.0f;
	}

	//	�`��ʒu
	auto draw = GetGameObject()->transform_.WorldPosition() - offset;

	//	�`��T�C�Y
	auto size = size_ * scale_;

	//	�`��
	DrawExtendGraphF(draw.x, draw.y, draw.x + size.x, draw.y + size.y, texture_->GetHandle(), TRUE);

} // draw
