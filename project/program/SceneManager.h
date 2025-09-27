#pragma once
#include<memory>

#include"singleton.h"
#include"Scene.h"
#include"OverlayScene.h"



/// <summary>
/// 画面インスタンスの管理
/// overlayでポーズやトランスの追加
/// </summary>
class SceneManager : public Singleton<SceneManager> {
	friend class Singleton<SceneManager>;
	SceneManager();
	virtual ~SceneManager() = default;

public:
	void Initialize();
	void Update();
	void Render();

	//	シーン内の破棄されたGameObjectを削除
	void DestoryGameObjects() {
		if (scene_) scene_->RemoveDestroyedObjects();
	}

	template<typename SC>
	void ChangeScene() {
		auto scPtr = std::make_unique<SC>();
		if (dynamic_cast<Scene*>(scPtr.get())) {
			scene_ = std::move(scPtr);
		}
	}

	template<typename Over>
	void CreateOverlay() {
		auto overPtr = std::make_unique<Over>();
		if (dynamic_cast<OverlayScene*>(overPtr.get())) {
			overlayScene_ = std::move(overPtr);
		}
	}

	void AddGameObject(std::shared_ptr<GameObject> a_gameObject) {

			scene_->AddGameObject(a_gameObject);

	}

private:
	std::unique_ptr<Scene> scene_;
	std::unique_ptr<OverlayScene> overlayScene_;
};