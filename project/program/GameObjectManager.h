#pragma once
#include"singleton.h"
#include"GameObject.h"

class GameObjectManager : public Singleton<GameObjectManager> {
	friend class Singleton<GameObjectManager>;
	GameObjectManager() = default;
	~GameObjectManager() = default;


	using GameObejctPtrVector = std::vector<std::shared_ptr<GameObject>>;

public:
	//	GameObjectの追加
	void AddGameObject( std::shared_ptr<GameObject> obj) {
		gameObjects_.push_back(obj);
	}

	//	すべての更新処理
	void Update() {
		for (auto& obj : gameObjects_) {
			if (obj) obj->Update();
		}
	}

	//	削除フラグが立っているGameObjectを削除する
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


	//	すべてのGameObjectの削除
	void AllDestroy() {
		gameObjects_.clear();
	}

	//	検索したタグを持つGameObjectのリスト取得
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
	GameObejctPtrVector  gameObjects_;	//	管理しているGameObjectのリスト

};