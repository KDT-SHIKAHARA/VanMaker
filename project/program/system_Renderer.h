#pragma once
#include"singleton.h"
#include"Drawable.h"


#include<vector>
#include<DxLib.h>

/// <summary>
/// 描画可能なインスタンスの描画システム
/// </summary>
class RendererSystem : public Singleton<RendererSystem> {
	friend class Singleton<RendererSystem >;
	RendererSystem() = default;
	~RendererSystem() = default;
public:

	//	追加
	void RegisterRenderer(std::shared_ptr<Drawable> renderer) {
		if (!renderer) return;
		int layer = renderer->GetLayer();
		if (layer >= renderers_.size()) {
			renderers_.resize(layer + 1);
		}
		renderers_[layer].push_back(renderer);
	}

	//	更新
	void Update() {
		//	インスタンスの破棄されているものをコレクションから削除
		for (auto& layer : renderers_) {
			layer.erase(
				std::remove_if(
					layer.begin(),
					layer.end(),
					[](const std::weak_ptr<Drawable>& renderer) {
						// lock() が失敗したら expired
						return renderer.expired();
					}
				),
				layer.end()
			);

		}

		//	レイヤー番号の小さい順に描画
		for (auto& layer : renderers_) {
			for (auto& renderer : layer) {
				auto lender = renderer.lock();
				if (lender && lender->isVisible_) {
					lender->Draw();
				}
			}
		}
	}

	//	すべて削除
	void Clear() {
		renderers_.clear();
	}

private:
	//	レイヤー番号＜インスタンスのコレクション＜参照用の生ポインタ＞＞
	std::vector<std::vector<std::weak_ptr<Drawable>>> renderers_;
};