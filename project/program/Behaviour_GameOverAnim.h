#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"vector2d.h"

class GameOverAnim : public MonoBehaviour, public Drawable {
public:
	GameOverAnim(const Vector2Df& a_targetPos, float lifeTime, int a_layer)
		:Drawable(a_layer), targetPos_(a_targetPos), lifeTime_(lifeTime)
	{
	}

	void Initialize()override;
	void Update()override;
	void Draw()override;

private:
	//	ëäéËÇÃç¿ïW
	Vector2Df targetPos_;
	float lifeTime_;
};