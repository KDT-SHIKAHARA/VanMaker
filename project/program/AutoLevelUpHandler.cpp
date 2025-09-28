#include "AutoLevelUpHandler.h"
#include "GameObject.h"
#include "comp_Weapon.h"
#include "random.h"

/// <summary>
/// 今所持している武器の中でレベルが最大じゃないものだけ強化をする
/// </summary>
void AutoLevelUpHandler::randomUpgradeExistingWeapon()
{
	//	武器生成管理コンポーネントの取得
	auto weapon_comp = obj_.lock()->GetComponent<WeaponComponent>();
	if (!weapon_comp) return;

	//	武器リストの取得
	auto weapons = weapon_comp->GetWeapons();
	if (weapons.empty()) return;

	//	レベルが最大じゃない武器のリスト
	std::vector<WeaponBase*> candidates;

	//	レベルが最大じゃなかったらリストに追加
	for (auto w : weapons) {
		if (w->IsLevelMax()) continue;
		candidates.push_back(w);
	}

	//	追加処理後にリストが空だったら処理を行わない
	if (candidates.empty()) return;

	//	そのリストからランダムに1つ選ぶ
	// 候補からランダムに1つ選択
	int idx = Random::RandomInt(0, static_cast<int>(candidates.size()) - 1);

	//	レベルアップ
	candidates[idx]->AdvanceLevel();
}

AutoLevelUpHandler::AutoLevelUpHandler(std::shared_ptr<GameObject> a_obj)
	:obj_(a_obj)
{

}

//	呼び出しの制御は外部が行う
//	あくまで呼び出されたらランダムで武器の強化をするクラス
void AutoLevelUpHandler::HandleLevelUp()
{
	//	武器のランダム強化
	randomUpgradeExistingWeapon();

}
