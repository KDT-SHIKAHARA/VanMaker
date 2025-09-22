#pragma once
#include"Component.h"
#include"Drawable.h"
#include"Resource.h"
#include"vector2d.h"
#include"flag.h"

#include<memory>
#include<string>

//	��_
enum class Pivot {
	TopLeft,
	Center,
};

/// <summary>
/// �摜�`��R���|�[���l���g
/// </summary>
class Image : public Component, public Drawable {
public:
	Image(int a_layer,const std::string& a_filePath, Pivot a_pivot = Pivot::TopLeft);
	virtual ~Image() = default;
	virtual void Update() override {};
	virtual void Draw() override;
protected:
	Vector2Df scale_{ 1.0f,1.0f };	//	�\���X�P�[��
	Vector2Df size_;	//	�摜�̃T�C�Y
	std::shared_ptr<Resource> texture_;	//	�摜���\�[�X
	Pivot pivot_;	//	��_
public:
	Flag isTrans_ = Flag::On;	//	���߃t���O
};
