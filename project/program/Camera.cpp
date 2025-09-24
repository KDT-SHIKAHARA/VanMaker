#include "Camera.h"
#include "data_Window.h"

#include<algorithm>

//	初期値
Camera::Camera() 
	:position_({ (float)WindowData::m_sceneW / 2,(float)WindowData::m_sceneH / 2 })
	, follow_position_(position_)
	,size_({ (float)WindowData::m_sceneW,(float)WindowData::m_sceneH })
	, cameraMin_({ 0,0 }), cameraMax_(size_)
	,mode_(Mode::Fixed)
	,isLimit_(Flag::Off)
{

}

//	後からinitializeしてもいいよ
void Camera::Initialize(const Vector2Df& position, const Vector2Df& size)
{
	
}

void Camera::Update()
{
	switch (mode_)
	{
		//	固定
	case Camera::Mode::Fixed:
		break;
	
		//	追従
	case Camera::Mode::Follow:
		position_ = follow_position_;
		//	制限があれば
		if (isLimit_) {
			//	画面の限界地の座標を計算
			auto position_min = cameraMin_ + (size_ / 2.f);
			auto position_max = cameraMax_ - (size_ / 2.f);

			//	カメラ座標を限界地に固定する
			position_.x = std::clamp(position_.x, position_min.x, position_max.x);
			position_.y = std::clamp(position_.y, position_min.y, position_max.y);



		}

		break;
	default:
		break;
	}
}
