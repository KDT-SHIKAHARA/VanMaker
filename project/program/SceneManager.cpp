#include "SceneManager.h"


//	基礎になるスクリーンがない場合は処理しない（更新、描画）

void SceneManager::Update()
{
	if (!scene_) return;

	//	存在判定
	if (overlayScene_) {
		overlayScene_->Update();
		//	終了フラグで削除
		if (overlayScene_->isFinish) overlayScene_.reset();
		return;
	}
	scene_->Update();
}

void SceneManager::Render()
{
	if (!scene_) return;
	scene_->Render();
	if (overlayScene_) {
		overlayScene_->Render();
	}
}
