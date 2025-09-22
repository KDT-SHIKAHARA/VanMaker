#pragma once
#include"Component.h"
#include"Drawable.h"
#include"Resource.h"

#include<memory>
#include<string>

//	基準点
enum class Pivot {
	TopLeft,
	Center,
};

/// <summary>
/// 画像描画コンポーンネント
/// </summary>
class Image : public Component, public Drawable {
public:
	Image(int a_layer, Pivot a_pivot,std::string a_filePath);
	virtual ~Image() = default;
	virtual void Draw() override;
protected:
	Vector2Df scale_{ 1.0f,1.0f };	//	表示スケール
	Vector2Df size_;	//	画像のサイズ
	std::shared_ptr<Resource> texture_;	//	画像リソース
	Pivot pivot_;	//	基準点

};
