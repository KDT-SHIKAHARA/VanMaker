#pragma once
#include"singleton.h"


/// ゲーム全体のデータベース
class GameDataBase : public Singleton<GameDataBase> {
	friend class Singleton<GameDataBase>;
	GameDataBase() = default;
	~GameDataBase() = default;
public:

};