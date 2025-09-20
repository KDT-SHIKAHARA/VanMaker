#pragma once
#include"singleton.h"
#include"GameObject.h"

class GameObjectManager : public Singleton<GameObjectManager> {
	friend class Singleton<GameObjectManager>;
	GameObjectManager() = default;
	~GameObjectManager() = default;


	using GameObejctPtrVector = std::vector<std::shared_ptr<GameObject>>;

public:
	//	GameObject�̒ǉ�
	void AddGameObject( std::shared_ptr<GameObject> obj) {
		gameObjects_.push_back(obj);
	}

	//	���ׂĂ̍X�V����
	void Update() {
		for (auto& obj : gameObjects_) {
			if (obj) obj->Update();
		}
	}

	//	�폜�t���O�������Ă���GameObject���폜����
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


	//	���ׂĂ�GameObject�̍폜
	void AllDestroy() {
		gameObjects_.clear();
	}

	//	���������^�O������GameObject�̃��X�g�擾
	GameObejctPtrVector FindGameObjectsByTag(GameObjectTag tag) {
		GameObejctPtrVector result;
		for (auto& obj : gameObjects_) {
			if (obj && obj->tag_ == tag) {
				result.push_back(obj);
			}
		}
		return result;
	}

private:
	GameObejctPtrVector  gameObjects_;	//	�Ǘ����Ă���GameObject�̃��X�g

};