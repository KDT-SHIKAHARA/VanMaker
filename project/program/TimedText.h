#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"vector2d.h"

#include<string>

/// <summary>
/// 表示の時間制限付きの文字列描画コンポーネント
/// </summary>
class TextTimed : public MonoBehaviour, public Drawable {
public:
	TextTimed(const std::string& a_draw, const Vector2Df& a_position, float a_displayTime, unsigned int a_color);
	void Update()override;
	void Draw()override;

private:
	Vector2Df position_;
	float displayTime_;
	unsigned int color_;
	std::string draw_;
};
