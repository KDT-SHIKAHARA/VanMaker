#pragma once
#include"WeaponBase.h"

//	雷を生成して参照経由で有効無効と処理を動かすクラス
class Thunderbolt : public WeaponBase {
	//	インスタンスの生成
	void create();

	

public:
	Thunderbolt();

	//	クールタイムの管理

	//	初期化
	void Initialize()override;
	//	発火
	void Fire()override;
	//	更新
	void Update()override;
	//	

private:
};