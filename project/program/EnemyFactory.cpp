#include "EnemyFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "db_Game.h"
#include "comp_animation.h"
#include "comp_EnemyFollowPlayer .h"
#include "comp_Health.h"
#include "comp_DrawCollider.h"

#include<stdexcept>

/// <summary>
/// �w�肳�ꂽID�Ɋ�Â��ēG�I�u�W�F�N�g�𐶐����A���L�|�C���^�Ƃ��ĕԂ��܂��B
/// </summary>
/// <param name="id">��������G�I�u�W�F�N�g�̎��ʎq�B</param>
/// <returns>�������ꂽ�G�I�u�W�F�N�g�ւ�std::shared_ptr�B</returns>
std::shared_ptr<GameObject> EnemyFactory::CreateEnemy(int id, int anim_id)
{
	//	�f�[�^�擾
	auto data = GameDataBase::Instance().GetEnemyData(id);
	auto anim_data = GameDataBase::Instance().GetAnimData(anim_id);
	auto size_data = GameDataBase::Instance().GetEnemySizeData(data->sizeTypeId);

	//	�C���X�^���X����
	auto enemy = std::make_shared<GameObject>();

	//	�ړ���
	enemy->AddComponent<Rigidbody>();

	//	�����蔻��
	enemy->AddComponent<RectCollider>(Vector2Df{(float)size_data->base_width,(float)size_data->base_height });

	//	�A�j���[�V����
	auto anim = enemy->AddComponent<AnimationComp>(anim_data->layer);
	anim->AddAnim(anim_data->name, anim_data->filePath, anim_data->animFirstFrame, anim_data->animLastFrame,0.2f,size_data->exrate);

	//	�v���C���[�Ɍ����Ĉړ�
	enemy->AddComponent<EnemyFollowPlayer>(1);


	//	�����蔻��̉���
	enemy->AddComponent<DrawRectColliderComp>();



	//	�̗�
	auto hp = enemy->AddComponent<Health>(1.0, data->hp);

	//	�^�O
	enemy->tag_ = GameObjectTag::Enemy;
	return enemy;
}
