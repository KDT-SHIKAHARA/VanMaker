#include "Image.h"
#include"GameObject.h"


#include<DxLib.h>

Image::Image(int a_layer, Pivot a_pivot, std::string a_filePath)
{

}

void Image::Draw()
{
	if (!texture_) return;	//	nullptr�`�F�b�N
	if (!texture_->HasHandle()) return;	// 	�n���h���`�F�b�N
	if (!isVisible_) return;	//	�\���t���O�`�F�b�N
	
	//	�`��ʒu
	auto draw = GetGameObject()->transform_.WorldPosition();

	//	�`��̊�_
	float offsetX = 0.0f;
	float offsetY = 0.0f;

	

}
