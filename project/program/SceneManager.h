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
	SceneManager() = default;
	virtual ~SceneManager() = default;

public:
	void Update();

	//	シーン内の破棄されたGameObjectを削除
	void DestoryGameObjects() {
		if (scene_) scene_->RemoveDestroyedObjects();
	}

	template<typename SC>
	void ChangeScene() {
		auto scPtr = std::make_unique<SC>();
		if (dynamic_cast<Scene*>(scPtr.get())) {
			scene_ = scPtr;
		}
	}

	template<typename Over>
	void CreateOverlay() {
		auto overPtr = std::make_unique<Over>();
		if (dynamic_cast<OverlayScene*>(overPtr.get())) {
			overlayScene_ = overPtr;
		}
	}


private:
	std::unique_ptr<Scene> scene_;
	std::unique_ptr<OverlayScene> overlayScene_;
};