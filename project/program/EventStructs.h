#pragma once
#include<vector>
#include<string>
#include"vector2d.h"

//	レベルアップ関係呼び出し
struct LevelUpEvent {
};

//	表示時間限定版メッセ時の表示event用
struct TimedMessageRenderEvent {
	std::string messages;	//	表示するメッセージ
	Vector2Df position;	//	表示する座標
	float displayTime;	//	表示する
	unsigned int color;	//	色
};

//	表示時間無制限メッセ表示
struct MessageRenderEvent {
	std::string messages;	//	表示するメッセージ
	Vector2Df position;	//	表示する座標
	unsigned int color;	//	色
	int size;	//	文字のサイズ
};

//	撃破数
struct KillCount {
};