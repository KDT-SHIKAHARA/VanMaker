#include "Image.h"
#include"GameObject.h"


#include<DxLib.h>

Image::Image(int a_layer, Pivot a_pivot, std::string a_filePath)
{

}

void Image::Draw()
{
	if (!texture_) return;	//	nullptrチェック
	if (!texture_->HasHandle()) return;	// 	ハンドルチェック
	if (!isVisible_) return;	//	表示フラグチェック
	
	//	描画位置
	auto draw = GetGameObject()->transform_.WorldPosition();

	//	描画の基準点
	float offsetX = 0.0f;
	float offsetY = 0.0f;

	

}
