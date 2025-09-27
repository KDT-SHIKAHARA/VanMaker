#include "DropExperienceComp.h"
#include "GameObject.h"
#include "GameObjectRequestAdd.h"
#include "db_Game.h"
#include "comp_Collider.h"
#include "comp_DrawCollider.h"
#include "DebugMacro.h"
#include "comp_image.h"

//	�C���X�^���X�̐��������Ēǉ�����
void DropExperienceComp::create()
{
	//	�f�[�^�̎擾
	auto data = GameDataBase::Instance().GetDropExpData(id_);
	auto texture = GameDataBase::Instance().GetImageData(data->texture_id);

	//	�C���X�^���X�̐���
	auto obj = std::make_shared<GameObject>();

	//	���W�ݒ�
	const auto& pos = GetGameObject()->transform_.WorldPosition();
	obj->transform_.SetPosition(pos);

	//	�����蔻��
	obj->AddComponent<RectCollider>(Vector2Df{ data->width,data->height });

	//	�����蔻��̉���
	if (DebugFlag::DrawCollider) {
		obj->AddComponent<DrawRectColliderComp>(texture->layer + 1);
	}

	//	�\��
	obj->AddComponent<ImageComponent>(texture->filePath, texture->exRate, texture->layer);

	//	�R���N�V�����ɒǉ�
	GameObjectQueue::Instance().Enqueue(obj);
}

DropExperienceComp::DropExperienceComp(int id)
	:id_(id)
{

}

void DropExperienceComp::Initialize()
{
	hp_ = GetGameObject()->GetComponentAsBase<Health>();
}

void DropExperienceComp::Update()
{
	//	�Q�Ɗm�F
	auto hp = hp_.lock();
	if (!hp) return;

	//	��������
	if (!hp->alive_) {
		//	�܂��h���b�v���Ă��Ȃ�������
		if (!dropped_) {
			//	����������
			create();
			//	�����ς݂ɂ���
			dropped_ = true;
		}
	}
}
