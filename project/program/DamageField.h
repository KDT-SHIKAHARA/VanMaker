#pragma once
#include"WeaponBase.h"

//	ダメージフィールド（ニンニクみたいな）の生成クラス
class DamageField : public WeaponBase {
public:

	//	GameObjectの生成

	//	生成のクールタイムなどの管理

	DamageField();
	void Initialize()override;
	void Fire()override;
	void Update()override;
protected:
	//	インスタンスの生成
	void create();
};