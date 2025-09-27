#include "comp_exp.h"
#include "db_Game.h"
#include"DxLib.h"
#include"data_Window.h"
#include"Collision.h"
#include"GameObject.h"
#include"DropExpBehaviour.h"
#include"GetColor.h"

void ExpComp::levelUp()
{
	//	レベルの上昇処理
	currentExp_ -= nextExp_;
	currentLevel_++;

	//	データ取得
	auto data = GameDataBase::Instance().GetExpTable(tableID);

	//	例外の経験値かどうか
	if (auto it = data->overrides.find(currentLevel_); it != data->overrides.end()) {
		nextExp_ = it->second;
	}
	//	通常処理
	else {
		nextExp_ = static_cast<int>(data->baseExp * std::pow(data->growthFactor, currentLevel_ - 1));
	}

}

ExpComp::ExpComp(int a_tableID, int layer)
	:Drawable(layer),tableID(a_tableID), currentExp_(0), currentLevel_(1)

{
	auto data = GameDataBase::Instance().GetExpTable(tableID);
	nextExp_ = data->baseExp;
}

void ExpComp::Update()
{
	//	レベルが上がっているかどうかの判定
	while (currentExp_ >= nextExp_){
		//	レベルアップ
		levelUp();
	} 
}

void ExpComp::Draw()
{
	//	座標の設定
	// 座標設定
	int x = 0;
	int y = 0;

	auto width = WindowData::m_sceneW;
	auto height = WindowData::m_sceneH / 20;

	// 経験値割合
	float ratio = static_cast<float>(currentExp_) / nextExp_;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	// 経験値バーの表示
	DrawBox(x, y, x + width, y + height, GetColor(100, 100, 100), true); // 背景
	DrawBox(x, y, x + static_cast<int>(width * ratio), y + height, GetColor(0, 200, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//	表示位置
	auto level_x = WindowData::m_sceneW - 70;
	auto level_y = height / 2;


	//	数値表示
	DrawFormatString(level_x, level_y, WHITE, "Lv:%3d", currentLevel_);
}

//	
void ExpComp::OnCollisionEnter(const Collision& collision)
{
	//	特定のタグだけ
	if (collision.other->tag_ == GameObjectTag::Exp) {
		//	経験値のコンポーネントを取得
		auto exp = collision.other->GetComponent<DropExpBehaviour>();
		if (!exp) return;

		//	経験値を加算してフラグを折る
		AddExp(exp->GetDropExp());
		collision.other->isDestory_.Set(Flag::On);

	}

}
