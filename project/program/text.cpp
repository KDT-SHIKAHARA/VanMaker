#include "text.h"
#include "vector2d.h"

#include<DxLib.h>

Text::Text(int a_layer, const std::string& a_text, int a_fontSize, Pivot a_pivot)
	:Drawable(a_layer), Component(), text_(a_text), fontSize_(a_fontSize), pivot_(a_pivot)
{
	fontHandle_ = CreateFontToHandle(nullptr, fontSize_, -1, DX_FONTTYPE_ANTIALIASING);
}

void Text::Draw()
{
	if(fontHandle_ == -1) return;	//	�t�H���g�n���h���`�F�b�N
	if (!isVisible_) return;	//	�\���t���O�`�F�b�N

	//	�`��̊�_
	auto offset = Vector2Df{ 0.0f,0.0f };

	//	���S��Ȃ�
	if(pivot_ == Pivot::Center){
		int w, h;
	}
}
