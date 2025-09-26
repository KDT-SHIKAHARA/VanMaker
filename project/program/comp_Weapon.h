#pragma once
#include"MonoBehaviour.h"
#include"WeaponBase.h"

#include<memory>
#include<vector>
#include<functional>
#include<unordered_map>

/// <summary>
/// 武器生成のコレクションを管理するコンポーネント
/// </summary>
class WeaponComponent : public MonoBehaviour {
public:
	WeaponComponent();
	virtual ~WeaponComponent() = default;
	void Update()override;
	void CreateWeapon(int a_id);
protected:
	//	生成メソッド
	std::unordered_map<int, std::function<std::unique_ptr<WeaponBase>()>> creates_;

	//	生成した武器生成クラスのコレクション
	std::vector<std::unique_ptr<WeaponBase>> weapons_;
};
