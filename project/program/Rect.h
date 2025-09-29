#pragma once
#include"Drawable.h"
#include"MonoBehaviour.h"
#include"vector2d.h"

class Rect : public MonoBehaviour, public Drawable {
public:
	Rect(const Vector2Df& size, unsigned int color, int alpha, int layer)
		: Drawable(layer)
		, size_(size)
		, color_(color)
		, alpha_(alpha)
	{
	}

	void Update()override {};
	void Draw()override;

	//	アクセサ
	void SetSize(const Vector2Df& size) { size_ = size; }
	void SetColor(unsigned int color) { color_ = color; }
	void SetAlpha(int alpha) { alpha_ = alpha; }
private:
	Vector2Df size_;
	unsigned int color_;
	int alpha_;
};