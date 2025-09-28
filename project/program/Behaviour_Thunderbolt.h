#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"vector2d.h"

//	サンダーボルト本体の挙動
//	表示まで担当する
class ThunderboltBehaviour : public MonoBehaviour, public Drawable {
public:
	ThunderboltBehaviour(const Vector2Df& a_targetPos,float lifeTime,int a_layer)
		:Drawable(a_layer),targetPos_(a_targetPos), lifeTime_(lifeTime)
	{ }

	void Initialize()override;
	void Update()override;
	void Draw()override;

private:
	//	相手の座標
	Vector2Df targetPos_;
	float lifeTime_;

};

