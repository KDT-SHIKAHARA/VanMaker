#pragma once
#include<memory>

#include"flag.h"

class Drawable : public std::enable_shared_from_this<Drawable> {
public:
	Drawable(int layer = 0);
	virtual ~Drawable() = default;

	void AddRegister();

	//	描画処理
	virtual void Draw() = 0;

	//	描画レイヤーの取得
	int GetLayer()const { return layer_; }
	//	描画レイヤーの設定
	void SetLayer(int layer) { layer_ = layer; }

protected:
	int layer_;	//	描画レイヤー
public:
	Flag isVisible_ = Flag::On; //	表示フラグ
};