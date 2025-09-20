#include "SceneManager.h"


void SceneManager::Update()
{
	//	‘¶İ”»’è
	if (overlayScene_) {
		overlayScene_->Update();
		//	I—¹ƒtƒ‰ƒO‚Åíœ
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
