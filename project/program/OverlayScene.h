#pragma once
#include<vector>
#include<memory>

#include"GameObjectManager.h"
#include"flag.h"

class GameObject;
class OverlayScene {
public:
	virtual void Initialize(){}
	virtual void Update() = 0;
	virtual void Render() = 0;

	//	GameObject‚Ì’Ç‰Á
	void AddGameObject(std::shared_ptr<GameObject> obj) {
		if (obj) {
			gameObjects_.push_back(obj);
			GameObjectRegistry::Instance().AddGameObject(obj);
		}
	}
protected:
	std::vector<std::shared_ptr<GameObject>> gameObjects_;

public:
	Flag isFinish = false;
};