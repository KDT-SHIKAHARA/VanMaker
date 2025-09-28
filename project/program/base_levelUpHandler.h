#pragma once

/// <summary>
/// レベルアップで強化するクラスのインターフェース
/// </summary>
class LevelUpHandler {
public:
	virtual ~LevelUpHandler() = default;

	//	レベルアップ処理
	virtual void HandleLevelUp() = 0;

};