#pragma once

//	�X�N���[�����Ƃ̏������s���X�N���v�g�̊��N���X
class SceneScript {
public:
	virtual ~SceneScript() = default;
	virtual void Update() = 0;
};