#include "DamageField.h"
#include "GameObjectManager.h"
#include "GameObjectTag.h"
#include "comp_Collider.h"
#include "comp_Rigidbody.h"
#include "comp_DrawCollider.h"
#include "DamageFieldBehavior.h"
#include "comp_Attack.h"
#include "db_Game.h"
#include "time.h"
#include "GameObjectRequestAdd.h"
#include "comp_image.h"
#include"DebugMacro.h"

DamageField::DamageField()
{
	create();
}

void DamageField::Initialize()
{
	
}

void DamageField::Fire()
{
}

//	�N�[���^�C���̌���
void DamageField::Update()
{
	if (current_ct_ > 0) {
		current_ct_ -= Time::deltaTime();
	}

}


void DamageField::create()
{

	//	�ԍ�����f�[�^�擾
	auto data = GameDataBase::Instance().GetWeaponData(1001);
	auto image_data = GameDataBase::Instance().GetImageData(data->textureID);

	//	�����������̈���擾���Ă���
	for (size_t i = 0; i < data->num; i++) {
		//	�C���X�^���X�̐���
		auto obj = std::make_shared<GameObject>();

		//	�R���|�[�l���g�̒ǉ�

		
		//	�����蔻��
		obj->AddComponent<CircleCollider>(data->radius);
		if (DebugFlag::DrawCollider) {
			//	�����蔻��̉���
			obj->AddComponent<DrawCircleColliderComp>();
		}
		//	����
		obj->AddComponent<DamagerFieldBehaviour>();

		//	�U��
		obj->AddComponent<AttackComp>(data->attack, data->slip_ct);

		//	�\��
		obj->AddComponent<ImageComponent>(image_data->filePath, image_data->exRate, image_data->layer);

		//	�^�O�̐ݒ�
		obj->tag_ = GameObjectTag::Weapon;

		//	�ǉ����X�g�ɒǉ�
		GameObjectQueue::Instance().Enqueue(obj);
	}


}