#include "comp_Weapon.h"
#include"DamageField.h"
#include"weapon_Thunderbolt.h"
#include"GameObject.h"

/// <summary>
/// 生成メソッドの初期化
/// </summary>
WeaponComponent::WeaponComponent(int a_use_weapon_list_id)
	:use_weapon_list_id_(a_use_weapon_list_id)
{
	creates_[301000] = [] {return std::make_unique<DamageField>(); };
	creates_[302000] = [] {return std::make_unique<Thunderbolt>(); };
}

void WeaponComponent::Update()
{

	if (GetGameObject()->isDead_) return;

	////	クールタイムを見て発火する
	//for (auto& weapon : weapons_) {

	//	//	インスタンスが存在するとき
	//	if (weapon) {

	//		//	発射可能状態なら
	//		if (weapon->IsReady()) {

	//			//	発火する
	//			weapon->Fire();
	//		}
	//	}
	//}

	//	更新処理
	for (auto& weapon : weapons_) {
		if (weapon) weapon->Update();
	}
}

/// <summary>
/// 武器を生成するクラスの生成
/// </summary>
/// <param name="a_id"> 生成する武器のid </param>
std::string WeaponComponent::CreateWeapon(int a_id)
{
	auto it = creates_.find(a_id);
	if (it != creates_.end()) {
		//	生成クラスを生成
		auto weapon = it->second();

		//	名前取得
		std::string name = weapon->GetName();

		//
		weapon->Initialize();

		//	インスタンスをコレクションに追加
		weapons_.push_back(std::move(weapon));

		//	番号を追加
		weapons_id_.insert(a_id);

		return name;
	}
}
