#include "Camera.h"
#include "data_Window.h"

#include<algorithm>

//	�����l
Camera::Camera() 
	:position_({ (float)WindowData::m_sceneW / 2,(float)WindowData::m_sceneH / 2 })
	, follow_position_(position_)
	,size_({ (float)WindowData::m_sceneW,(float)WindowData::m_sceneH })
	, cameraMin_({ 0,0 }), cameraMax_(size_)
	,mode_(Mode::Fixed)
	,isLimit_(Flag::Off)
{

}

//	�ォ��initialize���Ă�������
void Camera::Initialize(const Vector2Df& position, const Vector2Df& size)
{
	
}

void Camera::Update()
{
	switch (mode_)
	{
		//	�Œ�
	case Camera::Mode::Fixed:
		break;
	
		//	�Ǐ]
	case Camera::Mode::Follow:
		position_ = follow_position_;
		//	�����������
		if (isLimit_) {
			//	��ʂ̌��E�n�̍��W���v�Z
			auto position_min = cameraMin_ + (size_ / 2.f);
			auto position_max = cameraMax_ - (size_ / 2.f);

			//	�J�������W�����E�n�ɌŒ肷��
			position_.x = std::clamp(position_.x, position_min.x, position_max.x);
			position_.y = std::clamp(position_.y, position_min.y, position_max.y);



		}

		break;
	default:
		break;
	}
}
