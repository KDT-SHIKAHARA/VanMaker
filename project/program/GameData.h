#pragma once
#include<string>


//	プレイヤーのデータ構造
struct PlayerData {
	int id;				//	キャラのid
	std::string name;	//	名前
	std::string filePath;	//	画像ファイルパス
	int weaponId;	//	武器のid
	int hp;			//	体力の最大値
	int expTableId;		//	経験値テーブルのid
};


//	敵キャラのデータ構造
struct EnemyData {
	int id;	//	データID
	std::string name;	//	名前
	std::string texturePath;	//	画像ファイルパス
	int sizeTypeId;	//	サイズテーブル
	int hp;	//	体力
	int	attack;	//	攻撃力
	int behaviorId;		//	挙動パターン
	int dropExpId;	//	ドロップする経験値のテーブル
};

// 武器のデータ構造
struct WeaponData {
	int id;	//	データID
	std::string name;	//	名前
	std::string texturePath;	//	画像ファイルパス
	int attack;	//	攻撃力
	float attackInterval;	//	攻撃間隔
	int behaviorId;	//	武器パターン
};

//	敵キャラのサイズデータ構造
struct EnemySizeType {
	int id;	//	データID
	float scale;	//	表示スケール
};

//	経験値のテーブルデータ構造
struct ExpTable {
	int level;	//	レベル
	int requiredExp;	//	必要経験値
};


