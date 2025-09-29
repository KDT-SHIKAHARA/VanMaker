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
	
	UIClickComponent(const Vector2Df& a_size)
		:size_(a_size){ }

	void SetOnClick(CallBack cb) { onClick_ = std::move(cb); }
	void SetOnHover(CallBack cb) { onHover_ = std::move(cb); }


	void Update()override {
		//	マウス座標
		const auto& mouse = Input::GetMousePos();
		//	ゲームオブジェクトの座標取得
		const auto& pos = GetGameObject()->transform_.WorldPosition();

		// 中心基準での判定
		float halfW = size_.x * 0.5f;
		float halfH = size_.y * 0.5f;

		bool hover = (mouse.x >= pos.x - halfW && mouse.x <= pos.x + halfW &&
			mouse.y >= pos.y - halfH && mouse.y <= pos.y + halfH);

		//	重なっているときでまだ処理を行っていないとき
		if (hover && !isHover_) {
			//	メソッド呼び出し
			if (onHover_) onHover_();
		}

		//	フラグの更新
		isHover_ = hover;

		//	重なっているとき＆決定入力されているとき
		if (hover && Input::IsActionTriggered(Action::Select)) {
			if (onClick_) onClick_();
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

protected:
	Vector2Df size_;	//	サイズ
	bool isHover_ = false;		//	マウス座標が上に載っているかどうか
	CallBack onClick_;	//	クリック処理
	CallBack onHover_;	//	重なっているときの処理（色替えウィンドウなど）
};