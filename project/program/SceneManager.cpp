#include "SceneManager.h"
#include "InGame.h"


//	基礎になるスクリーンがない場合は処理しない（更新、描画）


SceneManager::SceneManager()
{
	
}

void SceneManager::Initialize()
{
	if (scene_)
	{
		scene_->Initialize();
	}
}

void SceneManager::Update()
{

	if (scene_) {
		//	存在判定
		if (overlayScene_) {
			overlayScene_->Update();
			//	終了フラグで削除
			if (overlayScene_->isFinish) {
				overlayScene_.reset();
			}
		}
		else {
			scene_->Update();
		}
	}



	//	更新後に切り替え
	if (pendingChange_) {
		pendingChange_();
		pendingChange_ = nullptr;
	}
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


