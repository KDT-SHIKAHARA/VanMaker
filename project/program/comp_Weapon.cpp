#include "comp_Weapon.h"

/// <summary>
/// �������\�b�h�̏�����
/// </summary>
WeaponComponent::WeaponComponent()
{
	//	�������\�b�h�����������悤��

}

void WeaponComponent::Update()
{
	//	�N�[���^�C�������Ĕ��΂���
	for (auto& weapon : weapons_) {

		//	�C���X�^���X�����݂���Ƃ�
		if (weapon) {

			//	���ˉ\��ԂȂ�
			if (weapon->IsReady()) {

				//	���΂���
				weapon->Fire();
			}
		}
	}

	//	�X�V����
	for (auto& weapon : weapons_) {
		if (weapon) weapon->Update();
	}
}

/// <summary>
/// ����𐶐�����N���X�̐���
/// </summary>
/// <param name="a_id"> �������镐���id </param>
void WeaponComponent::CreateWeapon(int a_id)
{
	auto it = creates_.find(a_id);
	if (it != creates_.end()) {
		//	�����N���X�𐶐�
		auto weapon = it->second();

		//	�C���X�^���X���R���N�V�����ɒǉ�
		weapons_.push_back(std::move(weapon));

	}
}
