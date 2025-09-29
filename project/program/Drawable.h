#pragma once
#include<memory>

#include"flag.h"

class GameObject;
class Drawable : public std::enable_shared_from_this<Drawable> {
public:
	Drawable(int layer = 0);
	virtual ~Drawable() = default;

	void AddRegister();

	void SetObj(std::shared_ptr<GameObject> a_obj) {
		obj_ = a_obj;
	}

	std::shared_ptr<GameObject> GetObj() {
		return obj_.lock();
	}

	//	描画処理
	virtual void Draw() = 0;

	//	描画レイヤーの取得
	int GetLayer()const { return layer_; }
	//	描画レイヤーの設定
	void SetLayer(int layer) { layer_ = layer; }

protected:
	std::weak_ptr<GameObject> obj_;
	int layer_;	//	描画レイヤー
public:
	Flag isVisible_ = Flag::On; //	表示フラグ
};