#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"vector2d.h"

class ReflectionRingBehaviour : public MonoBehaviour, public Drawable {
public:
    ReflectionRingBehaviour(float speed, float duration, float radius);
	void Initialize()override;
	void Update()override;
	void Draw()override;


private:
    Vector2Df velocity_;
    float speed_;
    float lifeTime_;
    float radius_;
};

