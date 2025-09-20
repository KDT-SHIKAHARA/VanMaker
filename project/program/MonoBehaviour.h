#pragma once
#include"Component.h"

struct Collision;
class MonoBehaviour :public Component{
public:
	virtual ~MonoBehaviour() = default;
	virtual void OnCollisionEnter(const Collision& collision) {};
};