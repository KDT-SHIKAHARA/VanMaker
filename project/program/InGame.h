#pragma once
#include"Scene.h"

class InGame : public Scene {
public:
	InGame();
	virtual ~InGame() = default;
	virtual void Initialize() override;
	void Render() override;
	void End()override;
private:
	int stageID_;
};