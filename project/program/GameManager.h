#pragma once
#include"singleton.h"
#include "data_Window.h"
#include<DxLib.h>
#include"RemFPS.h"

class GameManager : public Singleton<GameManager> {
	friend class Singleton<GameManager>;
	GameManager();
	virtual ~GameManager() = default;
	//	�f�[�^���\�[�X�̓ǂݍ���

	//	�e�N�X�`�����\�[�X�̓ǂݍ���
public:
	/// <summary>
	/// �E�B���h�E�̍쐬�Ə�����
	/// </summary>
	void Initialize();

	/// <summary>
	/// �Q�[�����[�v
	/// ��ʂ̍X�V�ƃX�N���[���̍X�V���s���Ă���B
	/// </summary>
	void Run();

	/// <summary>
	/// �E�B���h�E�̍폜�A���\�[�X�̉��
	/// </summary>
	void Exit();
private:
	RemFPS fps_;		//	fps�̌Œ�ƕ\��
	bool isRunning_;	//	�Q�[�����[�v�̎��s�t���O true: ���s  false: �I��

};