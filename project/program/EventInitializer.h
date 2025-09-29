#pragma once

class EventInitializer {
	//	レベルアップ関係
	static void LevelUp();

	//	文字列の表示系
	static void ScreenTextMessage();

	//	撃破数
	static void KillCountUp();

public:
	//	eventの初期化
	static void InitializeEvents();
};