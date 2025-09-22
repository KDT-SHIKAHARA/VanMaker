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
	std::string text_;	//	�\���e�L�X�g
	int fontHandle_ = -1;	//	�t�H���g�n���h��
	int fontSize_ = 12;	//	�t�H���g�T�C�Y
	Pivot pivot_;	//	��_

};