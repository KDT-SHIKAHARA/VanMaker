#pragma once
#include<memory>
#include<vector>

#include"flag.h"
#include"GameData.h"

class GameObject;
//	インスタンス(GameObject)と参照の管理
class WeaponBase {
public:
	//	初期化
	WeaponBase()
		:max_ct_(0), current_ct_(0), enable_(Flag::On)
	{ }

	virtual ~WeaponBase() = default;

	//	初期化
	virtual void Initialize() = 0;

	//	発火
	virtual void Fire() = 0;

	//	更新
	virtual void Update() = 0;

	//	クールタイムが経過しているかどうか
	//	true: 経過	false: クールタイム中
	bool IsReady() {
		return current_ct_ <= 0;
	}

protected:
	//	生成したインスタンスの参照
	std::vector<std::weak_ptr<GameObject>> attackObject_;

	//	クールタイム
	double max_ct_;

	//	切り替え用の経過時間
	double current_ct_;
public:

	//	有効判定
	Flag enable_;

};