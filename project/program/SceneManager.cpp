#include "SceneManager.h"
#include "InGame.h"

//	基礎になるスクリーンがない場合は処理しない（更新、描画）


SceneManager::SceneManager()
{
	ChangeScene<InGame>();
}

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
	//	存在判定
	if (!scene_) return;
	scene_->Render();

	//	存在判定
	if (overlayScene_) {
		overlayScene_->Render();
		return;
	}
}


