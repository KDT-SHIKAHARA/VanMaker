#pragma once
#include"Scene.h"
#include"GameObject.h"

#include<memory>

class Title : public Scene {
public:
	Title();
	virtual ~Title();
	virtual void Initialize() override;
	void End()override;
private:
	void createStartButton();
	void createTitleLogo();
	void createGuide();
};