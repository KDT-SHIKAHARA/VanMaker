#pragma once
#include"Component.h"
#include"flag.h"
#include"vector2d.h"

enum class ColliderType {
	Circle,
	Rect,
};

/// <summary>
/// 当たり判定を行うかどうかの判定用基底コンポーネント
/// </summary>
class Collider : public Component {
public:
	virtual ~Collider() = default;
	virtual ColliderType GetColliderType()const = 0;
	virtual void Update() override {};
public:
	Flag isTrigger_ = true;	//	当たり判定を行うかどうかのフラグ
	Flag isPushed_ = false;		//	押し戻し処理を行うかどうかのフラグ
};


/// <summary>
/// 円形コライダーを表すクラス
/// </summary>
class CircleCollider : public Collider {
public:
	CircleCollider(float arg_radius = 1.0f) :radius_(arg_radius) {}
	virtual ~CircleCollider() = default;
	virtual ColliderType GetColliderType()const override { return ColliderType::Circle; }
	float GetRadius()const { return radius_; }
private:
	float radius_;	//	半径
};


/// <summary>
/// 矩形コライダーを表すクラス
/// </summary>
class RectCollider : public Collider {
	public:
	RectCollider(const Vector2Df& arg_size = { 1.0f,1.0f }) :size_(arg_size) {}
	virtual ~RectCollider() = default;
	virtual ColliderType GetColliderType()const override { return ColliderType::Rect; }

	Vector2Df GetSize()const { return size_; }
private:
	Vector2Df size_;	//	サイズ
};