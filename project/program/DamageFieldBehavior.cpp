#include "DamageFieldBehavior.h"
#include "GameObjectManager.h"
#include "GameObjectTag.h"
#include "comp_image.h"

void DamagerFieldBehaviour::Update()
{
	//	�v���C���[�̍��W���擾
	auto player = GameObjectRegistry::Instance().FindGameObjectsByTag(GameObjectTag::Player);

	//	���g�̍��W���v���C���[�Ɠ������W�ɂ���
	GetGameObject()->transform_.SetPosition(player[0]->transform_.WorldPosition());

	auto image = GetGameObject()->GetComponent<ImageComponent>();
	if (image) {
		image->AddAngle(angle_speed_);
	}


}
