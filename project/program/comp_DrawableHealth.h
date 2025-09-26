#pragma once
#include"comp_Health.h"
#include"Drawable.h"
#include"DxlibRap.h"
#include"GameObject.h"
#include"GetColor.h"

/// <summary>
/// 体力クラスに表示機能を付けた拡張版
/// </summary>
class DrawableHealth : public Health, public Drawable {
public:
	DrawableHealth(const double& a_max_invi, int a_max_hp,int layer, const Vector2Df& a_size)
		:Health(a_max_invi, a_max_hp), Drawable(layer), size_(a_size){ }
	virtual ~DrawableHealth() = default;

	void Draw()override {
		//if (IsHealthMax()) return;

		//	座標取得
		const auto& pos = GetGameObject()->transform_.WorldPosition();

		//	オフセット分ずらす
		auto drawpos = pos + offset_;

		//	左上の座標
		auto leftup = drawpos - (size_ / 2.f);

		//	右下
		auto rightdown = leftup + size_;

		//	全長の長さ * 体力の割合でバーの長さを設定
		auto filledWidth = size_.x * Percent();

		//	可変する右下座標　左座標＋サイズ
		auto filled_rightdown = leftup + Vector2Df{ filledWidth,size_.y };

		//	ベース
		RapperDxlib::DrawBoxAACamera(leftup, rightdown, BLACK, TRUE);
		//	色
		RapperDxlib::DrawBoxAACamera(leftup, filled_rightdown, RED, TRUE);
		//	枠
		RapperDxlib::DrawBoxAACamera(leftup, rightdown, BLACK, FALSE, 2.0f);

	}

	//	アクセサ　
	void SetOffset(const Vector2Df& a_offset) { offset_ = a_offset; }
	void SetSize(const Vector2Df& a_size) { size_ = a_size; }

protected:
	Vector2Df size_;
	Vector2Df offset_;
};

