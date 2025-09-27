#pragma once
#include"Component.h"
#include"flag.h"
#include"vector2d.h"

enum class ColliderType {
	Circle,
	Rect,
};

/// <summary>
/// �����蔻����s�����ǂ����̔���p���R���|�[�l���g
/// </summary>
class Collider : public Component {
public:
	virtual ~Collider() = default;
	virtual ColliderType GetColliderType()const = 0;
	virtual void Update() override {};
public:
	Flag isTrigger_ = true;	//	�����蔻����s�����ǂ����̃t���O
	Flag isPushed_ = false;		//	�����߂��������s�����ǂ����̃t���O
};


/// <summary>
/// �~�`�R���C�_�[��\���N���X
/// </summary>
class CircleCollider : public Collider {
public:
	CircleCollider(float arg_radius = 1.0f) :radius_(arg_radius) {}
	virtual ~CircleCollider() = default;
	virtual ColliderType GetColliderType()const override { return ColliderType::Circle; }
	float GetRadius()const { return radius_; }
private:
	float radius_;	//	���a
};


/// <summary>
/// ��`�R���C�_�[��\���N���X
/// </summary>
class RectCollider : public Collider {
	public:
	RectCollider(const Vector2Df& arg_size = { 1.0f,1.0f }) :size_(arg_size) {}
	virtual ~RectCollider() = default;
	virtual ColliderType GetColliderType()const override { return ColliderType::Rect; }

	Vector2Df GetSize()const { return size_; }
private:
	Vector2Df size_;	//	�T�C�Y
};