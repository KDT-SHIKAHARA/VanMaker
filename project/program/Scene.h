#pragma once
#include"GameObject.h"
#include"GameObjectManager.h"
#include"SceneSclipt.h"
#include"GameObjectRequestAdd.h"

#include<vector>
#include<memory>

class Scene {
public:
	Scene() = default;
	~Scene() = default;
	virtual void Initialize() {};
	
	virtual void Update() {
		//	script�̍X�V
		for(auto& script : scripts_){
			if(script) script->Update();
		}

		//	�C���X�^���X�̏��n
		if (!GameObjectQueue::Instance().empty()) {
			for (auto& obj : GameObjectQueue::Instance().Flush()) {
				AddGameObject(obj);
			}
		}

		//	�I�u�W�F�N�g�̍X�V
		for (auto& obj : gameObjects_) {
			if (obj) obj->Update();
		}
	};

	virtual void Render() {}

	//	�C���X�^���X�̔j��
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

	//	GameObject�̒ǉ�
	void AddGameObject(std::shared_ptr<GameObject> obj) {
		if (obj) {
			gameObjects_.push_back(obj);
			GameObjectRegistry::Instance().AddGameObject(obj);
		}
	}

protected:
	std::vector<std::shared_ptr<GameObject>> gameObjects_;
	std::vector<std::unique_ptr<SceneScript>> scripts_;
};