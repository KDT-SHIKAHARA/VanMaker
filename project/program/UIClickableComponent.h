#pragma once
#include"MonoBehaviour.h"
#include"InputManager.h"
#include"vector2d.h"
#include"GameObject.h"

#include<functional>

class UIClickComponent : public MonoBehaviour {
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

		//	重なっているかどうかの判定
		bool hover = (mouse.x >= pos.x && mouse.x <= pos.x + size_.x &&
			mouse.y >= pos.y && mouse.y <= pos.y + size_.y);

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

protected:
	Vector2Df size_;	//	サイズ
	bool isHover_ = false;		//	マウス座標が上に載っているかどうか
	CallBack onClick_;	//	クリック処理
	CallBack onHover_;	//	重なっているときの処理（色替えウィンドウなど）
};