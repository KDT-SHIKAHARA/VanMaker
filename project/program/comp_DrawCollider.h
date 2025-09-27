#pragma once
#include"MonoBehaviour.h"
#include"comp_Collider.h"
#include"Drawable.h"
#include"DxlibRap.h"
#include"GameObject.h"
#include"GetColor.h"

#include<memory>

class DrawRectColliderComp : public MonoBehaviour, public Drawable {
public:
	DrawRectColliderComp(int layer = 3)
		:Drawable(layer){ }

	void Initialize()override {
		collider_ = GetGameObject()->GetComponent<RectCollider>();
	}

	void Update()override {

	}

	void Draw()override {
		const auto& size = collider_.lock()->GetSize();
		const auto& pos = GetGameObject()->transform_.WorldPosition();

		auto draw1 = pos - (size / 2.f);
		auto draw2 = pos + (size / 2.f);

		RapperDxlib::DrawBoxAACamera(draw1, draw2, RED, FALSE, 2.0f);
	}


	void OnCollisionEnter(const Collision& collision)override {

	}

private:
	std::weak_ptr<RectCollider> collider_;

};


class DrawCircleColliderComp : public MonoBehaviour, public Drawable {
public:
	DrawCircleColliderComp()
		:Drawable(3){ }

	void Initialize()override {
		collider_ = GetGameObject()->GetComponent<CircleCollider>();
	}

	void Update()override {

	}

	void Draw()override {
		const auto& pos = GetGameObject()->transform_.WorldPosition();
		const auto& radius = collider_.lock()->GetRadius();

		RapperDxlib::DrawCircleAACamera(pos, radius, 25, RED, FALSE, 2.0f);

	};

private:
	std::weak_ptr<CircleCollider> collider_;

};


