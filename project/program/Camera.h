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
	//	初期化
	void Initialize(const Vector2Df& position, const Vector2Df& size);
	//	更新
	void Update();

	//	位置設定
	void SetPosition(const Vector2Df& position) { position_ = position; }
	//	位置取得
	Vector2Df GetPosition()const { return position_; }
	//	サイズ設定
	void SetSize(const Vector2Df& size) { size_ = size; }
	//	サイズ取得
	Vector2Df GetSize()const { return size_; }
	//	表示範囲左上設定
	void SetCameraMin(const Vector2Df& min) { cameraMin_ = min; isLimit_ = Flag::On; }
	//	表示範囲右下設定
	void SetCameraMax(const Vector2Df& max) { cameraMax_ = max; isLimit_ = Flag::On; }
	//	表示範囲左上取得
	Vector2Df GetCameraMin()const { return cameraMin_; }
	//	表示範囲右下取得
	Vector2Df GetCameraMax()const { return cameraMax_; }
	//	モード設定
	void SetMode(Mode mode) { mode_ = mode; }
	//	モード取得
	Mode GetMode()const { return mode_; }

	void SetFollowPosition(const Vector2Df& position) { follow_position_ = position; }

private:
	Vector2Df position_;	//	位置
	Vector2Df follow_position_;	//	追従する座標
	Vector2Df cameraMin_;	//	表示範囲左上
	Vector2Df cameraMax_;	//	表示範囲右下
	Vector2Df size_;		//	サイズ
	Mode mode_;				//	モード
	Flag isLimit_;			//	範囲制限フラグ
	

};
