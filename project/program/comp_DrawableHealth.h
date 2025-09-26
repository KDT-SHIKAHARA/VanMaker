#pragma once
#include"comp_Health.h"
#include"Drawable.h"
#include"DxlibRap.h"
#include"GameObject.h"
#include"GetColor.h"

/// <summary>
/// �̗̓N���X�ɕ\���@�\��t�����g����
/// </summary>
class DrawableHealth : public Health, public Drawable {
public:
	DrawableHealth(const double& a_max_invi, int a_max_hp,int layer, const Vector2Df& a_size)
		:Health(a_max_invi, a_max_hp), Drawable(layer), size_(a_size){ }
	virtual ~DrawableHealth() = default;

	void Draw()override {
		//if (IsHealthMax()) return;

		//	���W�擾
		const auto& pos = GetGameObject()->transform_.WorldPosition();

		//	�I�t�Z�b�g�����炷
		auto drawpos = pos + offset_;

		//	����̍��W
		auto leftup = drawpos - (size_ / 2.f);

		//	�E��
		auto rightdown = drawpos + (size_ / 2.f);

		//	�ς���E�����W�@�����W�{�T�C�Y
		auto RdPer = leftup + size_;
		RdPer.x *= Percent();

		//	�x�[�X
		RapperDxlib::DrawBoxAACamera(leftup, rightdown, BLACK, TRUE);
		//	�F
		RapperDxlib::DrawBoxAACamera(leftup, RdPer, RED, TRUE);
		//	�g
		RapperDxlib::DrawBoxAACamera(leftup, rightdown, BLACK, FALSE, 2.0f);

	}

	//	�A�N�Z�T�@
	void SetOffset(const Vector2Df& a_offset) { offset_ = a_offset; }
	void SetSize(const Vector2Df& a_size) { size_ = a_size; }

protected:
	Vector2Df size_;
	Vector2Df offset_;
};

