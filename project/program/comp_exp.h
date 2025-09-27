#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"

/// <summary>
/// �o���l�o�[�̕\���ƃ��x���̊Ǘ��ƍ��̎擾�o���l�A���̃��x��
/// </summary>
class ExpComp : public MonoBehaviour, public Drawable {
protected:

	//	���x���A�b�v�̏���
	void levelUp();
public:
	ExpComp(int a_tableID,int layer = 3);


	//	�o���l��ǉ�����B
	void AddExp(float a_dropExp) {
		if (a_dropExp < 0) return;
		currentExp_ += a_dropExp;
	}

	//	�Փ˂����Ƃ��Ɍo���l���擾����

	void Update()override;
	void Draw()override;
	void OnCollisionEnter(const Collision& collision)override;

protected:
	//	���̃��x��
	int currentLevel_;
	//	���̌o���l
	float currentExp_;
	//	���̃��x���܂ł̕K�v�o���l
	float nextExp_;
	//	�o���l�e�[�u����ID
	int tableID;
};