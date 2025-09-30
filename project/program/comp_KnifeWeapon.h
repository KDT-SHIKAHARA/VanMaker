#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"vector2d.h"

class KnifeBehaviour : public MonoBehaviour{
public:
	KnifeBehaviour(const Vector2Df& a_duration, float a_speed);
	void Update()override;
	void OnCollisionEnter(const Collision& collision) {};

private:
	//	ˆÚ“®•ûŒü
	Vector2Df velocity_;
	//	‰æ–ÊŠOƒtƒ‰ƒO
	bool OutScene_;
};

