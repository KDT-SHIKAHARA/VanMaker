#pragma once
#include"singleton.h"
#include"GameObject.h"

class GameObjectRegistry : public Singleton<GameObjectRegistry> {
	friend class Singleton<GameObjectRegistry>;
	GameObjectRegistry() = default;
	~GameObjectRegistry() = default;

	using GameObjectWeakPtrVector = std::vector<std::weak_ptr<GameObject>>;
	using GameObjectSharedPtrVector = std::vector<std::shared_ptr<GameObject>>;

public:
	//	GameObject�̒ǉ�
	void AddGameObject( std::shared_ptr<GameObject> obj) {
		gameObjects_.push_back(obj);
	}

	//	���ׂĂ̍X�V����
	void Update() {
		//	���g�����݂��Ȃ�GameObject���폜
		gameObjects_.erase(std::remove_if(gameObjects_.begin(), gameObjects_.end(),
			[](const std::weak_ptr<GameObject>& obj) { return obj.expired(); }),
			gameObjects_.end());
	}


	//	���ׂĂ�GameObject�̍폜
	void AllDestroy() {
		gameObjects_.clear();
	}

	//	���������^�O������GameObject�̃��X�g�擾
	GameObjectSharedPtrVector FindGameObjectsByTag(GameObjectTag tag) {
		std::vector<std::shared_ptr<GameObject>>  result;
		for (auto& obj_weak : gameObjects_) {
			auto obj = obj_weak.lock();
			if (obj && obj->tag_ == tag) {
				result.push_back(obj);
			}
		}
		return result;
	}

private:
	GameObjectWeakPtrVector  gameObjects_;	//	�Ǘ����Ă���GameObject�̃��X�g

};