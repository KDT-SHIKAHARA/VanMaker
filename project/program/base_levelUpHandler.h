#pragma once
#include<string>

/// <summary>
/// レベルアップで強化するクラスのインターフェース
/// </summary>
class LevelUpHandler {
public:
	virtual ~LevelUpHandler() = default;

	//	レベルアップ処理
	virtual std::string HandleLevelUp() = 0;
};