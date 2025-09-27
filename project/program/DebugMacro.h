#pragma once


//	�f�o�b�N�t���O�Ǘ�
struct DebugFlag
{
//	�f�o�b�N���̂�

#ifdef _DEBUG
	//	�v���C���[�̖��G
	static constexpr bool PlayerInvi = true;

	//	�G�̗̑͂̕\��
	static constexpr bool EnemyDrawHpBar = true;

	//	�����蔻��̉���
	static constexpr bool DrawCollider = true;

#else
//	�t���O�̖�����
	static constexpr bool PlayerInvi = false;
	static constexpr bool EnemyDrawHpBar = false;
	static constexpr bool DrawCollider = false;


#endif // _DEBUG

};



