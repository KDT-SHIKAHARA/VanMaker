#include "SceneManager.h"


void SceneManager::Update()
{
	//	���ݔ���
	if (overlayScene_) {
		overlayScene_->Update();
		//	�I���t���O�ō폜
		if (overlayScene_->isFinish) overlayScene_.reset();
		return;
	}

	scene_->Update();
}

void SceneManager::Render()
{
	scene_->Render();
	overlayScene_->Render();
}
