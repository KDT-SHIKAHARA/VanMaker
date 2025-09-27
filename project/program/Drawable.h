#pragma once
#include<memory>

#include"flag.h"

class Drawable : public std::enable_shared_from_this<Drawable> {
public:
	Drawable(int layer = 0);
	virtual ~Drawable() = default;

	void AddRegister();

	//	�`�揈��
	virtual void Draw() = 0;

	//	�`�惌�C���[�̎擾
	int GetLayer()const { return layer_; }
	//	�`�惌�C���[�̐ݒ�
	void SetLayer(int layer) { layer_ = layer; }

protected:
	int layer_;	//	�`�惌�C���[
public:
	Flag isVisible_ = Flag::On; //	�\���t���O
};