#pragma once
#include"GameObject.h"
#include"GameObjectManager.h"


#include<vector>
#include<memory>

class Scene {
public:
	Scene() = default;
	~Scene() = default;
	virtual void Initialize() {};
	
	virtual void Update() {
		for (auto& obj : gameObjects_) {
			if (obj) obj->Update();
		}
	};
	
	virtual void Render() = 0;

	//	インスタンスの破棄
	void RemoveDestroyedObjects() {
		gameObjects_.erase(
			std::remove_if(
				gameObjects_.begin(),
				gameObjects_.end(),
				[](const std::shared_ptr<GameObject>& obj) {
					return obj->isDestory_;
				}),
			gameObjects_.end());
	}

	//	GameObjectの追加
	void AddGameObject(std::shared_ptr<GameObject> obj) {
		if (obj) {
			gameObjects_.push_back(obj);
			GameObjectRegistry::Instance().AddGameObject(obj);
		}
	}

protected:
	std::vector<std::shared_ptr<GameObject>> gameObjects_;
};