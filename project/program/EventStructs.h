#pragma once
#include<vector>
#include<string>
#include"vector2d.h"

struct LevelUpEvent {
};

//	メッセ時の表示event用
struct MessageRenderEvent {
	std::string messages;	//	表示するメッセージ
	Vector2Df position;	//	表示する座標
	float displayTime;	//	表示する
	unsigned int color;	//	色
};