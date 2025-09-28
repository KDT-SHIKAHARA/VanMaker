#include "Camera.h"
#include "data_Window.h"
#include "GameObjectManager.h"
#include "random.h"


#include<algorithm>


//	初期値
Camera::Camera() 
	:position_({ (float)WindowData::m_sceneW / 2,(float)WindowData::m_sceneH / 2 })
	, follow_position_(position_)
	,size_({ (float)WindowData::m_sceneW,(float)WindowData::m_sceneH })
	, cameraMin_({ 0,0 }), cameraMax_(size_)
	,mode_(Mode::Follow)
	,isLimit_(Flag::Off)
{

}

//	後からinitializeしてもいいよ
void Camera::Initialize(const Vector2Df& position, const Vector2Df& size)
{
	
}

void Camera::Update()
{
	switch (mode_)
	{
		//	固定
	case Camera::Mode::Fixed:
		break;
	
		//	追従
	case Camera::Mode::Follow:
		position_ = follow_position_;
		//	制限があれば
		if (isLimit_) {
			//	画面の限界地の座標を計算
			auto position_min = cameraMin_ + (size_ / 2.f);
			auto position_max = cameraMax_ - (size_ / 2.f);

			//	カメラ座標を限界地に固定する
			position_.x = std::clamp(position_.x, position_min.x, position_max.x);
			position_.y = std::clamp(position_.y, position_min.y, position_max.y);

		}

		break;
	default:
		break;
	}
}

std::vector<std::shared_ptr<GameObject>> Camera::GetObjectsInCameraWithTag(GameObjectTag a_tag, int count)
{
	//	タグからリストの取得
	const auto& list = GameObjectRegistry::Instance().FindGameObjectsByTag(a_tag);

	//	画面内の該当タグのインスタンスのコレクション
	std::vector<std::shared_ptr<GameObject>> candidates;

	//	そのタグのインスタンスの座標取得
	for (auto& e : list) {
		//	無効の時は判定せずfalse扱い
		if (!e->enable_) continue;

		//	座標を取得して範囲内なら追加
		if (Contains(e->transform_.WorldPosition())) {
			candidates.push_back(e);
		}

	}

	//	該当のインスタンスがなければnull状態
	if (candidates.empty()) {
		return std::vector<std::shared_ptr<GameObject>>();
	}

	//	画面内の数を越していたら選ぶ数を画面内の数にする
	//	ここも同じ敵を選んでいいなら処理を変更して
	int pickCount = (std::min)(count, static_cast<int>(candidates.size()));

	//	渡された回数分ランダムに選んで選ばれたインスタンスは最後に返す選ばれたインスタンスのリストに移動させる
	std::vector<std::shared_ptr<GameObject>> result;

	//	検索
	for (int i = 0; i < pickCount; i++) {
		int idx = Random::RandomInt(0, static_cast<int>(candidates.size() - 1));
		result.push_back(candidates[idx]);

		//	同じ敵に雷が落ちてもいいなら処理この処理をコメントにする。（多分忘れる）
		candidates.erase(candidates.begin() + idx);
	}

	return result;
}



