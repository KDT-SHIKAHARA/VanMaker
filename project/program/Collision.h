#pragma once
#include<memory>


class GameObject;
class Collider;
struct Collision
{
	std::shared_ptr<GameObject> other;	//	�ǂ̃I�u�W�F�N�g�������������킩��悤��
	std::shared_ptr<Collider> collider;	//	���ʂ��Ƃɕ�����ꍇ�ǂ�ɂ����������킩��悤��
	//	�K�v�ȏ�񂪑�����ꍇ�͂����ɒǉ�����
};