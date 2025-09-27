#pragma once
#include<string>
#include<unordered_map>

//	プレイヤーのデータ構造
struct PlayerData {
	int id;				//	キャラのid
	std::string name;	//	名前
	int weaponId;	//	武器のid
	int hp;			//	体力の最大値
	float speed;	//	移動速度
	int expTableId;		//	経験値テーブルのid
	float max_invi;	//	無敵時間の設置
	float size_w_;	//	サイズW
	float size_h_;	//	サイズH
};

//	プレイヤーのアニメーション用のデータ
struct AnimData {
	int id;				//	識別用id
	std::string name;	//	アニメーションの名前
	std::string filePath;	//	画像ファイルパス
	int animFirstFrame;	//	アニメーションの最初の番号
	int animLastFrame;	//	アニメーションの最後の番号
	int layer;		//	描画レイヤー
};

//	画像デーブル
struct ImageData {
	int id;	//	id
	std::string filePath;	//	フォルダのパス
	float exRate;	//	表示倍率
	int layer;	//	レイヤー番号
};

//	敵キャラのデータ構造
struct EnemyData {
	int id;	//	データID
	int sizeTypeId;	//	サイズテーブル
	int hp;	//	体力
	int	attack;	//	攻撃力
	float coolTime_;	//	クールタイム
	int behaviorId;		//	挙動パターン
	int dropExpId;	//	ドロップする経験値のテーブル
};

//	敵のサイズテーブル
struct EnemySizeData {
	int id;
	int base_width;
	int base_height;
	float exrate;
};

// 武器のデータ構造
struct WeaponData {
	int id;		//	id
	std::string name;	//	武器名
	float width;	//	横サイズ
	float height;	//	縦サイズ
	float radius;	//	半径
	float max_ct;	//	有効時間のクールタイム
	int attack;		//	攻撃力
	float slip_ct;	//	ダメージを与える間隔
	int num;		//	攻撃の数
	int textureID;	//	テクスチャのID
};

//	ドロップする経験値のテーブル
struct DropExpData {
	int id;
	int texture_id;
	int exp;
	float width;	//	横サイズ
	float height;	//	縦サイズ
};


//	敵キャラのサイズデータ構造
struct EnemySizeType {
	int id;	//	データID
	float scale;	//	表示スケール
};

//	経験値のテーブルデータ構造
struct ExpTable {
	int id;				//	id
	int baseExp;		//	基本経験値
	float growthFactor;	//	成長係数
	std::unordered_map<int, int> overrides;	//	特定のレベルの上書き
};


