#pragma once
#include<memory>

#include"singleton.h"
#include"Scene.h"
#include"OverlayScene.h"


/// <summary>
/// ��ʃC���X�^���X�̊Ǘ�
/// overlay�Ń|�[�Y��g�����X�̒ǉ�
/// </summary>
class SceneManager : public Singleton<SceneManager> {
	friend class Singleton<SceneManager>;
	SceneManager();
	virtual ~SceneManager() = default;

public:
	void Update();
	void Render();

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