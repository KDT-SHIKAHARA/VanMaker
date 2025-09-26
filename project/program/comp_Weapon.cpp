#include "comp_Weapon.h"

/// <summary>
/// 生成メソッドの初期化
/// </summary>
WeaponComponent::WeaponComponent()
{
	//	生成メソッドを初期化しようね

}

void WeaponComponent::Update()
{
	//	クールタイムを見て発火する
	for (auto& weapon : weapons_) {

		//	インスタンスが存在するとき
		if (weapon) {

			//	発射可能状態なら
			if (weapon->IsReady()) {

				//	発火する
				weapon->Fire();
			}
		}
	}

	//	更新処理
	for (auto& weapon : weapons_) {
		if (weapon) weapon->Update();
	}
}

/// <summary>
/// 武器を生成するクラスの生成
/// </summary>
/// <param name="a_id"> 生成する武器のid </param>
void WeaponComponent::CreateWeapon(int a_id)
{
	auto it = creates_.find(a_id);
	if (it != creates_.end()) {
		//	生成クラスを生成
		auto weapon = it->second();

		//	インスタンスをコレクションに追加
		weapons_.push_back(std::move(weapon));

	}
}
