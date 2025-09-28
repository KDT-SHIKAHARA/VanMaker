#pragma once
#include"MonoBehaviour.h"
#include"WeaponBase.h"

#include<memory>
#include<vector>
#include<functional>
#include<unordered_map>

/// <summary>
/// 武器生成のコレクションを管理するコンポーネント
/// 
/// </summary>
class WeaponComponent : public MonoBehaviour {
public:
	WeaponComponent();
	virtual ~WeaponComponent() = default;
	void Update()override;
	void CreateWeapon(int a_id);

	//	武器生成クラスのポインタ取得
	std::vector<WeaponBase*> GetWeapons() {
		std::vector<WeaponBase*> results;
		
		//	今存在している武器の種類分拡張をする
		results.reserve(weapons_.size());

		//	生ポインタを取得
		for (auto& w : weapons_) {
			results.push_back(w.get());
		}

		return results;
	}

protected:
	//	生成メソッド
	std::unordered_map<int, std::function<std::unique_ptr<WeaponBase>()>> creates_;

	//	生成した武器生成クラスのコレクション
	std::vector<std::unique_ptr<WeaponBase>> weapons_;
};
