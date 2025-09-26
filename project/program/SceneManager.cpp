#include "SceneManager.h"
#include "InGame.h"

//	��b�ɂȂ�X�N���[�����Ȃ��ꍇ�͏������Ȃ��i�X�V�A�`��j


SceneManager::SceneManager()
{
	ChangeScene<InGame>();
}

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
	//	���ݔ���
	if (!scene_) return;
	scene_->Render();

	//	���ݔ���
	if (overlayScene_) {
		overlayScene_->Render();
		return;
	}
}


