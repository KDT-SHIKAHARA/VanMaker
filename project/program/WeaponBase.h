#pragma once
#include<memory>
#include<vector>
#include<string>

#include"flag.h"
#include"GameData.h"

class GameObject;
//	インスタンス(GameObject)と参照の管理
class WeaponBase {
public:
	//	初期化
	WeaponBase()
		:max_ct_(0), current_ct_(1), enable_(Flag::On), level_(1), max_level_(1)
	{ }

	virtual ~WeaponBase() = default;

	//	初期化
	virtual void Initialize() = 0;

	//	発火
	virtual void Fire() = 0;

	//	更新
	virtual void Update() = 0;

	//	クールタイムが経過しているかどうか
	//	true: 経過	false: クールタイム中
	bool IsReady() {
		return current_ct_ <= 0;
	}


	//	アクセサ
	int GetLevel()const { return level_; }
	void SetLevel(int a_level) { 

		//	0以下なら
		if (a_level <= 0) {
			//	数値を更新しない
			return;
		}
		//	最大レベルを越していたら
		else if (a_level >= max_level_) {
			//	最大レベルで止める
			level_ = max_level_;
			return;
		}
		//	正常値ならそのまま代入
		level_ = a_level; 
	}

	/// <summary>
	/// レベルが最大かどうか
	/// </summary>
	/// <returns>true: 最大 false: 最大じゃない </returns>
	bool IsLevelMax()const
	{
		return level_ >= max_level_;
	}

	/// <summary>
	/// レベルの数値を次に進める
	/// </summary>
	void AdvanceLevel() {
		//	最大レベルより小さいとき
		if (max_level_ > level_) {
			//	レベルを次に進める
			level_++;
		}
	}

	//	名前の取得
	std::string GetName()const { return name_; }

protected:
	//	生成したインスタンスの参照
	std::vector<std::weak_ptr<GameObject>> attackObject_;

	//	クールタイム
	double max_ct_;

	//	切り替え用の経過時間
	double current_ct_;

	//	武器名
	std::string name_;

	//	レベル
	int level_;
	int max_level_;
public:

	//	有効判定
	Flag enable_;

};