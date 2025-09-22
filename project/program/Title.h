#pragma once
#include"Scene.h"

#include<memory>

class Title : public Scene {
public:
	Title();
	virtual ~Title() = default;
	virtual void Initialize() override;
	virtual void Update() override;

};