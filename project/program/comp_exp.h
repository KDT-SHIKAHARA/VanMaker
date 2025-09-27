#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"

/// <summary>
/// 経験値バーの表示とレベルの管理と今の取得経験値、次のレベル
/// </summary>
class ExpComp : public MonoBehaviour, public Drawable {
protected:

	//	レベルアップの処理
	void levelUp();
public:
	ExpComp(int a_tableID,int layer = 3);


	//	経験値を追加する。
	void AddExp(float a_dropExp) {
		if (a_dropExp < 0) return;
		currentExp_ += a_dropExp;
	}

	//	衝突したときに経験値を取得する

	void Update()override;
	void Draw()override;
	void OnCollisionEnter(const Collision& collision)override;

protected:
	//	今のレベル
	int currentLevel_;
	//	今の経験値
	float currentExp_;
	//	次のレベルまでの必要経験値
	float nextExp_;
	//	経験値テーブルのID
	int tableID;
};