#include "EnemyFactory.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "db_Game.h"
#include "comp_animation.h"
#include "comp_EnemyFollowPlayer .h"

#include<stdexcept>

/// <summary>
/// �w�肳�ꂽID�Ɋ�Â��ēG�I�u�W�F�N�g�𐶐����A���L�|�C���^�Ƃ��ĕԂ��܂��B
/// </summary>
/// <param name="id">��������G�I�u�W�F�N�g�̎��ʎq�B</param>
/// <returns>�������ꂽ�G�I�u�W�F�N�g�ւ�std::shared_ptr�B</returns>
std::shared_ptr<GameObject> EnemyFactory::CreateEnemy(int id)
{
	//	�f�[�^�擾
	auto data = GameDataBase::Instance().GetEnemyData(id);

	//	�C���X�^���X����
	auto enemy = std::make_shared<GameObject>();
	enemy->AddComponent<Rigidbody>();


	auto anim = enemy->AddComponent<AnimationComp>(1);
	anim->AddAnim("Idle", data->texturePath, data->animFirstFrame, data->animLastFrame);
	enemy->AddComponent<EnemyFollowPlayer>(1);

	return enemy;
}
