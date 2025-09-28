#include "AutoLevelUpHandler.h"
#include "GameObject.h"
#include "comp_Weapon.h"
#include "random.h"
#include "db_Game.h"

/// <summary>
/// 今所持している武器の中でレベルが最大じゃないものだけ強化をする
/// </summary>
std::string AutoLevelUpHandler::randomUpgradeExistingWeapon()
{

	std::string err = "生成できませんでした";
	//	武器生成管理コンポーネントの取得
	auto weapon_comp = obj_.lock()->GetComponent<WeaponComponent>();
	if (!weapon_comp) return err;

	//	武器リストの取得
	auto weapons = weapon_comp->GetWeapons();
	if (weapons.empty()) return err;

	//	レベルが最大じゃない武器のリスト
	std::vector<WeaponBase*> candidates;

	//	レベルが最大じゃなかったらリストに追加
	for (auto w : weapons) {
		if (w->IsLevelMax()) continue;
		candidates.push_back(w);
	}

	//	追加処理後にリストが空だったら処理を行わない
	if (candidates.empty()) return "";

	//	そのリストからランダムに1つ選ぶ
	// 候補からランダムに1つ選択
	int idx = Random::RandomInt(0, static_cast<int>(candidates.size()) - 1);

	//	今のレベルを取得
	auto oldLevel = candidates[idx]->GetLevel();

	//	レベルアップ
	candidates[idx]->AdvanceLevel();

	auto nextWeaponLevel = candidates[idx]->GetLevel();

	//	表示用の文字列 
	//	名前 + がLv + 前のレベル + → + 今のレベル + に強化！
	std::string result = candidates[idx]->GetName() + " が Lv" + std::to_string(oldLevel) +
		"→" + std::to_string(nextWeaponLevel) + "に強化！";

	return result;

}

//	新しい武器の生成
std::string AutoLevelUpHandler::addNewWeapon()
{

	std::string err = "生成できませんでした";

	//	プレイヤーの使用可能武器リスト番号を取得
	auto weapon_comp = obj_.lock()->GetComponent<WeaponComponent>();
	if (!weapon_comp) return err;

	//	使用可能な武器のリストをデータベースから取得
	auto allWeaponIds = GameDataBase::Instance().GetWeaponIDTable(weapon_comp->GetCanUseWeaposListId())->weaponIDs;

	//	所持している武器のリスト
	const auto& owned = weapon_comp->GetWeaponId();

	//	まだ持っていない武器IDを入れるコレクション
	std::vector<int> candidates;

	//	全てのIDと所持しているIDがあるかどうかを検索してまだ未所持ならコレクションに追加
	for (auto& id : allWeaponIds) {
		//	ヒットしなかったら
		if (owned.find(id) == owned.end()) {
			//	追加する
			candidates.push_back(id);
		}
	}

	//	選択肢がなければ終了
	if (candidates.empty()) return "";

	//	ランダムに１つ選ぶ
		// 候補からランダムに1つ選択
	int idx = Random::RandomInt(0, static_cast<int>(candidates.size()) - 1);
	auto name = weapon_comp->CreateWeapon(candidates[idx]);

	std::string draw =
		"新たな武器　" + name + " を入手した！";
	//	文字列を戻す
	return draw;
}

AutoLevelUpHandler::AutoLevelUpHandler(std::shared_ptr<GameObject> a_obj)
	:obj_(a_obj)
{

}

//	呼び出しの制御は外部が行う
//	あくまで呼び出されたらランダムで武器の強化をするクラス
std::string AutoLevelUpHandler::HandleLevelUp()
{
	//	一定確率で強化か新規追加を変えます。
	//	百分率で計算
	int choice = Random::RandomInt(0, 99);

	//	一旦デバック完了まで確率を固定するけどこれもエクセルで管理できるようにする。
	if (choice < 70) {
		//	武器のランダム強化
		return randomUpgradeExistingWeapon();
	}
	else {
		//	ランダムで新しい武器の生成
		return addNewWeapon();
	}


}
