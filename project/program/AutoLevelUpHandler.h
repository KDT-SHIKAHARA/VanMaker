#pragma once
#include"base_levelUpHandler.h"

#include<memory>

class GameObject;
//	自動的に武器を強化をするクラス
//	今回はランダムで行います。
//	一時的な参照でこのクラスを所有しているクラス経由でしか呼び出せない
//	なのでGameObjectが存在していないとこのクラスも呼び出されないから
// 参照が切れてもこのクラスが存在する事態は起きない

class AutoLevelUpHandler : public LevelUpHandler {

	//	武器のランダム強化
	std::string  randomUpgradeExistingWeapon();

	//	ランダムで新しい武器の取得
	std::string addNewWeapon();

public:
	//	ポインタの取得
	AutoLevelUpHandler(std::shared_ptr<GameObject> a_obj);

	//	自動的に強化する
	std::string HandleLevelUp()override;
private:
	//	強化する対象のオブジェクト
	std::weak_ptr<GameObject> obj_;
};