#include "SceneManager.h"


//	��b�ɂȂ�X�N���[�����Ȃ��ꍇ�͏������Ȃ��i�X�V�A�`��j

void SceneManager::Update()
{
	if (!scene_) return;

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
	if (!scene_) return;
	scene_->Render();
	if (overlayScene_) {
		overlayScene_->Render();
	}
}
