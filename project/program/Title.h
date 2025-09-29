#pragma once
#include"Scene.h"
#include"GameObject.h"

#include<memory>

class Title : public Scene {
public:
	Title();
	virtual ~Title() = default;
	virtual void Initialize() override;
private:
	void createStartButton();
};