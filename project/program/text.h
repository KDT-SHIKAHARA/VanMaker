#pragma once
#include"Component.h"
#include"Drawable.h"
#include"Resource.h"

#include<memory>
#include<string>

class Text : public Component, public Drawable {
public:
	enum class Pivot {
		TopLeft,
		Center,
	};
	Text(int a_layer, const std::string& a_text, int a_fontSize = 12, Pivot a_pivot = Pivot::TopLeft);
	virtual ~Text() = default;

	virtual void Update() override {};
	virtual void Draw()override;

protected:
	std::string text_;	//	表示テキスト
	int fontHandle_ = -1;	//	フォントハンドル
	int fontSize_ = 12;	//	フォントサイズ
	Pivot pivot_;	//	基準点

};