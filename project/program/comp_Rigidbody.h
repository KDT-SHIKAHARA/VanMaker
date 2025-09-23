#pragma once
#include"Component.h"
#include"vector2d.h"
#include"flag.h"


class Rigidbody : public Component {
public:
	Rigidbody(const Vector2Df& a_maxVelocity = { 500.0f,500.0f }, const Vector2Df& a_maxAcceleration = { 1000.0f,1000.0f },
		float a_mass = 1.0f, float a_drag = 0.0f, float a_gravity = 9.8)
		:velocity_({ 0,0 }), acceleration_({ 0,0 }), inputVelocity_({0,0}), mass_(a_mass), drag_(a_drag), maxVelocity_(a_maxVelocity), maxAcceleration_(a_maxAcceleration), gravity_(a_gravity),
		enableGravity_(Flag::Off), enableMovement_(Flag::On), canMoveX_(Flag::On), canMoveY_(Flag::On), isGraunded_(Flag::On), canInputMove_(Flag::On)
	{ }

	//	^����n
	//	�͂̉�����B���ʂ��l�����ĉ����x�ɕϊ�����
	void AddForce(const Vector2Df& force);

	//	^�A�N�Z�T
	Vector2Df GetVelocity()const { return velocity_;}	//	�ړ��ʂ̎擾
	void SetVelocity(const Vector2Df& a_velocity) { velocity_ = a_velocity; }//	�ړ��ʂ̐ݒ�
	void AddVelocity(const Vector2Df& a_velocity) { velocity_ += a_velocity; } //	�ړ��ʂ̒ǉ�
	Vector2Df GetAcceleration()const { return acceleration_; } //	�����x�̎擾
	void SetAcceleration(const Vector2Df& a_acceleration) { acceleration_ = a_acceleration; } //	�����x�̐ݒ�
	void AddAcceleration(const Vector2Df& a_acceleration) { acceleration_ += a_acceleration; } //	�����x�̒ǉ�
	float GetMass()const { return mass_; } //	�d���̎擾
	void SetMass(const float a_mass) { mass_ = a_mass; } //	�d���̐ݒ�


	//	������
	void Initialize() override;

	//	�X�V���� (�Ăяo���̓X�N���v�g�R���|�[�l���g�̏��������ׂďI����Ă���)
	//	�d�͂̈ړ��ʂ�ǉ��A�������s���B
	void Update() override;
	void Move(); //	�ړ��ʂ��ʒu�ɔ��f


private:
	//	^��{�f�[�^
	Vector2Df velocity_;		//	�ړ���
	Vector2Df acceleration_;	//	�����x
	Vector2Df inputVelocity_;	//	���͕��̈ړ���
	float mass_;				//	�d��
	float drag_;				//	������



	//	^���
	Vector2Df maxVelocity_;		//	�����x���
	Vector2Df maxAcceleration_;	//	���x���
	float gravity_;				//	�d�͂̋���


public:

	//	^����n
	Flag enableGravity_;		//	�d�̓t���O
	Flag enableMovement_;		//	�ړ��t���O
	Flag isGraunded_;			//	�n�ʐݒu�t���O
	Flag canInputMove_;			//	���͂ɂ��ړ��\����t���O
	Flag canMoveX_;				//	���ړ��\����t���O
	Flag canMoveY_;				//	�c�ړ��\����t���O


};