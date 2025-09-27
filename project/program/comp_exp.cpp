#include "comp_exp.h"
#include "db_Game.h"
#include"DxLib.h"
#include"data_Window.h"
#include"Collision.h"
#include"GameObject.h"
#include"DropExpBehaviour.h"
#include"GetColor.h"

void ExpComp::levelUp()
{
	//	���x���̏㏸����
	currentExp_ -= nextExp_;
	currentLevel_++;

	//	�f�[�^�擾
	auto data = GameDataBase::Instance().GetExpTable(tableID);

	//	��O�̌o���l���ǂ���
	if (auto it = data->overrides.find(currentLevel_); it != data->overrides.end()) {
		nextExp_ = it->second;
	}
	//	�ʏ폈��
	else {
		nextExp_ = static_cast<int>(data->baseExp * std::pow(data->growthFactor, currentLevel_ - 1));
	}

}

ExpComp::ExpComp(int a_tableID, int layer)
	:Drawable(layer),tableID(a_tableID), currentExp_(0), currentLevel_(1)

{
	auto data = GameDataBase::Instance().GetExpTable(tableID);
	nextExp_ = data->baseExp;
}

void ExpComp::Update()
{
	//	���x�����オ���Ă��邩�ǂ����̔���
	while (currentExp_ >= nextExp_){
		//	���x���A�b�v
		levelUp();
	} 
}

void ExpComp::Draw()
{
	//	���W�̐ݒ�
	// ���W�ݒ�
	int x = 0;
	int y = 0;

	auto width = WindowData::m_sceneW;
	auto height = WindowData::m_sceneH / 20;

	// �o���l����
	float ratio = static_cast<float>(currentExp_) / nextExp_;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	// �o���l�o�[�̕\��
	DrawBox(x, y, x + width, y + height, GetColor(100, 100, 100), true); // �w�i
	DrawBox(x, y, x + static_cast<int>(width * ratio), y + height, GetColor(0, 200, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//	�\���ʒu
	auto level_x = WindowData::m_sceneW - 70;
	auto level_y = height / 2;


	//	���l�\��
	DrawFormatString(level_x, level_y, WHITE, "Lv:%3d", currentLevel_);
}

//	
void ExpComp::OnCollisionEnter(const Collision& collision)
{
	//	����̃^�O����
	if (collision.other->tag_ == GameObjectTag::Exp) {
		//	�o���l�̃R���|�[�l���g���擾
		auto exp = collision.other->GetComponent<DropExpBehaviour>();
		if (!exp) return;

		//	�o���l�����Z���ăt���O��܂�
		AddExp(exp->GetDropExp());
		collision.other->isDestory_.Set(Flag::On);

	}

}
