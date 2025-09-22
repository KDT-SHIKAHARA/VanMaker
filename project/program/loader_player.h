#pragma once
#include<string>

class PlayerDataLoader {
	PlayerDataLoader() = default;
	~PlayerDataLoader() = default;

public:
	struct CsvData
	{
		int id;				//	キャラのid
		std::string name;	//	名前
		std::string filePath;	//	画像ファイルパス
		int weaponId;	//	武器のid
		int hp;			//	体力の最大値
		int expId;		//	経験値テーブルのid
	}; // struct



};	//	class