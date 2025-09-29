#pragma once
#include<memory>
#include<functional>

#include"singleton.h"
#include"Scene.h"
#include"OverlayScene.h"
#include"TransitionOverlay.h"

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
		pendingChange_ = [this]() {
			auto scPtr = std::make_unique<SC>();
			if (dynamic_cast<Scene*>(scPtr.get())) {
				scene_ = std::move(scPtr);
				scene_->Initialize();
			}
		};
	}

	template<typename Over>
	void CreateOverlay() {
		auto overPtr = std::make_unique<Over>();
		if (dynamic_cast<OverlayScene*>(overPtr.get())) {
			overlayScene_ = std::move(overPtr);
			overlayScene_->Initialize();
		}
	}

	//	オーバレイ付きの画面切り替え　
	template<typename SC>
	void ChangeSceneWithTransition() {
		auto changeAction = [this]() {
			auto scPtr = std::make_unique<SC>();
			if (dynamic_cast<Scene*>(scPtr.get())) {
				scene_ = std::move(scPtr);
				scene_->Initialize();
			}
		};

		// トランジションオーバーレイを生成
		overlayScene_ = std::make_unique<TransitionOverlay>(changeAction);
		overlayScene_->Initialize();
	}

	//	生成
	void AddGameObject(std::shared_ptr<GameObject> a_gameObject) {
		//	オーバーレイ中はオーバーレイに追加
		if (overlayScene_) {
			overlayScene_->AddGameObject(a_gameObject);
			return;
		}

		//	画面に追加
		scene_->AddGameObject(a_gameObject);

	}

private:
	std::unique_ptr<Scene> scene_;
	std::unique_ptr<OverlayScene> overlayScene_;
	std::function<void()> pendingChange_;
};