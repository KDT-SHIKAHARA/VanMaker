#pragma once
#include"Component.h"
#include"Drawable.h"
#include"Resource.h"

#include<memory>
#include<string>

class Text : public Component, public Drawable {
public:
	Text(const std::string& text, unsigned int color, bool center = true, int size = 16,int layer = 5);

	virtual void Update() override {};
	virtual void Draw()override;

	//	アクセサ
	void SetText(const std::string& a_text) { text_ = a_text; }
	void SetColor(unsigned int a_color) { color_ = a_color; }
protected:
	std::string text_;
	int fontHandle_;
	unsigned int color_;
	int size_; // 現状は未使用（固定フォント）
	bool center_;
};