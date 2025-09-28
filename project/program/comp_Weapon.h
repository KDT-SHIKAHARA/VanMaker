#pragma once
#include"MonoBehaviour.h"
#include"WeaponBase.h"

#include<memory>
#include<vector>
#include<functional>
#include<unordered_map>
#include<unordered_set>
#include<string>

/// <summary>
/// 武器生成のコレクションを管理するコンポーネント
/// </summary>
class WeaponComponent : public MonoBehaviour {
public:
	WeaponComponent(int a_use_weapon_list_id);
	virtual ~WeaponComponent() = default;
	void Update()override;
	std::string CreateWeapon(int a_id);

	//	武器生成クラスのポインタ取得
	std::vector<WeaponBase*> GetWeapons() {
		std::vector<WeaponBase*> results;
		
		//	今存在している武器の種類分拡張をする
		results.reserve(weapons_.size());

		//	生ポインタを取得
		for (auto& w : weapons_) {
			results.push_back(w.get());
		}

		//	コレクションを返す
		return results;
	}

	//	所持している武器のIDリスト
	std::unordered_set<int> GetWeaponId()const {
		return weapons_id_;
	}

	/// <summary>
	/// 使用可能な武器のリストの取得用ID
	/// </summary>
	/// <returns> id </returns>
	int GetCanUseWeaposListId()const {
		return use_weapon_list_id_;
	}

protected:
	//	今所持している武器のIDリスト
	std::unordered_set<int> weapons_id_;

	//	生成メソッド
	std::unordered_map<int, std::function<std::unique_ptr<WeaponBase>()>> creates_;

	//	生成した武器生成クラスのコレクション
	std::vector<std::unique_ptr<WeaponBase>> weapons_;

	int use_weapon_list_id_;
};
