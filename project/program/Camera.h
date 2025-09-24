#pragma once
#include"singleton.h"
#include"vector2d.h"
#include"flag.h"

class Camera : public Singleton<Camera> {
	friend class Singleton<Camera>;
	Camera();
	~Camera() = default;

	enum class Mode {
		Fixed,
		Follow,
	};
public:
	//	������
	void Initialize(const Vector2Df& position, const Vector2Df& size);
	//	�X�V
	void Update();

	//	�ʒu�ݒ�
	void SetPosition(const Vector2Df& position) { position_ = position; }
	//	�ʒu�擾
	Vector2Df GetPosition()const { return position_; }
	//	�T�C�Y�ݒ�
	void SetSize(const Vector2Df& size) { size_ = size; }
	//	�T�C�Y�擾
	Vector2Df GetSize()const { return size_; }
	//	�\���͈͍���ݒ�
	void SetCameraMin(const Vector2Df& min) { cameraMin_ = min; isLimit_ = Flag::On; }
	//	�\���͈͉E���ݒ�
	void SetCameraMax(const Vector2Df& max) { cameraMax_ = max; isLimit_ = Flag::On; }
	//	�\���͈͍���擾
	Vector2Df GetCameraMin()const { return cameraMin_; }
	//	�\���͈͉E���擾
	Vector2Df GetCameraMax()const { return cameraMax_; }
	//	���[�h�ݒ�
	void SetMode(Mode mode) { mode_ = mode; }
	//	���[�h�擾
	Mode GetMode()const { return mode_; }

	void SetFollowPosition(const Vector2Df& position) { follow_position_ = position; }

private:
	Vector2Df position_;	//	�ʒu
	Vector2Df follow_position_;	//	�Ǐ]������W
	Vector2Df cameraMin_;	//	�\���͈͍���
	Vector2Df cameraMax_;	//	�\���͈͉E��
	Vector2Df size_;		//	�T�C�Y
	Mode mode_;				//	���[�h
	Flag isLimit_;			//	�͈͐����t���O
	

};
