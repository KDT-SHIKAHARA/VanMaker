#pragma once
#include"camera.h"
#include"GameObject.h"
#include"MonoBehaviour.h"

class CameraFollow : public MonoBehaviour{
public:
	CameraFollow() = default;
	~CameraFollow() = default;
	void Update() override {
		const auto& pos = GetGameObject()->transform_.WorldPosition();
		Camera::Instance().SetFollowPosition(pos);
	}

};