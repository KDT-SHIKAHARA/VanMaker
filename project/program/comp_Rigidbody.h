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

	//	^操作系
	//	力の加える。質量を考慮して加速度に変換する
	void AddForce(const Vector2Df& force);

	//	^アクセサ
	Vector2Df GetVelocity()const { return velocity_;}	//	移動量の取得
	void SetVelocity(const Vector2Df& a_velocity) { velocity_ = a_velocity; }//	移動量の設定
	void AddVelocity(const Vector2Df& a_velocity) { velocity_ += a_velocity; } //	移動量の追加
	Vector2Df GetAcceleration()const { return acceleration_; } //	加速度の取得
	void SetAcceleration(const Vector2Df& a_acceleration) { acceleration_ = a_acceleration; } //	加速度の設定
	void AddAcceleration(const Vector2Df& a_acceleration) { acceleration_ += a_acceleration; } //	加速度の追加
	float GetMass()const { return mass_; } //	重さの取得
	void SetMass(const float a_mass) { mass_ = a_mass; } //	重さの設定


	//	初期化
	void Initialize() override;

	//	更新処理 (呼び出しはスクリプトコンポーネントの処理がすべて終わってから)
	//	重力の移動量を追加、減衰を行う。
	void Update() override;
	void Move(); //	移動量を位置に反映


private:
	//	^基本データ
	Vector2Df velocity_;		//	移動量
	Vector2Df acceleration_;	//	加速度
	Vector2Df inputVelocity_;	//	入力分の移動量
	float mass_;				//	重さ
	float drag_;				//	減衰量



	//	^上限
	Vector2Df maxVelocity_;		//	加速度上限
	Vector2Df maxAcceleration_;	//	速度上限
	float gravity_;				//	重力の強さ


public:

	//	^制御系
	Flag enableGravity_;		//	重力フラグ
	Flag enableMovement_;		//	移動フラグ
	Flag isGraunded_;			//	地面設置フラグ
	Flag canInputMove_;			//	入力による移動可能判定フラグ
	Flag canMoveX_;				//	横移動可能判定フラグ
	Flag canMoveY_;				//	縦移動可能判定フラグ


};