#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"Resource.h"
#include"vector2d.h"
#include"flag.h"

#include<string>

class ImageComponent : public MonoBehaviour, public Drawable {
public:
	//	����W
	enum class Pivot {
		TopLeft,
		Center
	};

	ImageComponent(const std::string& filePath, float a_exRate,int a_layer, ImageComponent::Pivot a_pivot = ImageComponent::Pivot::Center);
	void Update()override;
	void Draw()override;


	//	�A�N�Z�T
	void SetAngle(float a_anble) { angle_ = a_anble; }
	void AddAngle(float a_anble) { angle_ += a_anble; }
	
protected:

	//	�摜�̃T�C�Y
	Vector2Df size_;

	//	�摜���\�[�X
	std::shared_ptr<Resource> texture_;

	//	�e�k��
	float exRate_;

	//	��]
	float angle_;

	//	�s�|�b�g
	Pivot pivot_;

public:
	//	���E����
	Flag isTurn_;

	//	���߃t���O
	Flag isTrans_;

};



