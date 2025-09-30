#pragma once
#include"MonoBehaviour.h"
#include"InputManager.h"
#include"vector2d.h"
#include"GameObject.h"
#include"Drawable.h"
#include"DxlibRap.h"
#include"GetColor.h"
#include"DebugMacro.h"

#include<functional>

class UIClickComponent : public MonoBehaviour,public Drawable {
public:
	using CallBack = std::function<void()>;
	using HoverCallBack = std::function<void(bool)>;

	UIClickComponent(const Vector2Df& a_size,int layer = 11)
		:size_(a_size){ }

	void SetOnClick(CallBack cb) { onClick_ = std::move(cb); }
	void SetOnHover(HoverCallBack cb) { onHover_ = std::move(cb); }


	void Update()override {

		const auto& mouse = Input::GetMousePos();
		// --- マウス移動を検知したら強制モード解除 ---
		if (mouse.x != lastMousePos_.x || mouse.y != lastMousePos_.y) {
			forceHoverMode_ = false;
		}
		lastMousePos_ = mouse;


		if (!forceHoverMode_) {
			// マウス座標
			const auto& pos = GetGameObject()->transform_.WorldPosition();

			float halfW = size_.x * 0.5f;
			float halfH = size_.y * 0.5f;

			bool hover = (mouse.x >= pos.x - halfW && mouse.x <= pos.x + halfW &&
				mouse.y >= pos.y - halfH && mouse.y <= pos.y + halfH);

			if (hover != isHover_) {
				if (onHover_) onHover_(hover);
				isHover_ = hover;
			}

			if (Input::IsActionTriggered(Action::Select)) {
				if (onClick_) onClick_();
			}

			if (hover && Input::IsMouseOn(MOUSE_INPUT_LEFT)) {
				if (onClick_) onClick_();
			}
		}

	}

	void Draw()override {

		if (!DebugFlag::DrawCollider) return;
		
		//	座標
		const auto& pos = GetGameObject()->transform_.WorldPosition();

		//	後で変更しやすいように
		auto draw1 = pos - size_ / 2;

		auto draw2 = draw1 + size_;

		DrawBox(draw1.x, draw1.y, draw2.x, draw2.y, RED, FALSE);
	}

	// キーボード用に強制的に Hover 状態を変更
	void ForceHover(bool flag) {
		forceHoverMode_ = true;
		if (isHover_ != flag) {
			isHover_ = flag;
			if (onHover_) onHover_(flag);
		}
	}

	CallBack GetOnClick() const { return onClick_; }

protected:
	Vector2Df size_;	//	サイズ
	Vector2Di lastMousePos_{ -1, -1 };
	CallBack onClick_;	//	クリック処理
	HoverCallBack  onHover_;	//	重なっているときの処理（色替えウィンドウなど）
	bool forceHoverMode_ = false;  // キーボード操作中なら true
	bool isHover_ = false;		//	マウス座標が上に載っているかどうか

};