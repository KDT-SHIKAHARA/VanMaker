#pragma once
#include"singleton.h"
#include"Drawable.h"


#include<vector>
#include<DxLib.h>

/// <summary>
/// �`��\�ȃC���X�^���X�̕`��V�X�e��
/// </summary>
class RendererSystem : public Singleton<RendererSystem> {
	friend class Singleton<RendererSystem >;
	RendererSystem() = default;
	~RendererSystem() = default;
public:

	//	�ǉ�
	void RegisterRenderer(std::shared_ptr<Drawable> renderer) {
		if (!renderer) return;
		int layer = renderer->GetLayer();
		if (layer >= renderers_.size()) {
			renderers_.resize(layer + 1);
		}
		renderers_[layer].push_back(renderer);
	}

	//	�X�V
	void Update() {
		//	�C���X�^���X�̔j������Ă�����̂��R���N�V��������폜
		for (auto& layer : renderers_) {
			layer.erase(
				std::remove_if(
					layer.begin(),
					layer.end(),
					[](const std::weak_ptr<Drawable>& renderer) {
						// lock() �����s������ expired
						return renderer.expired();
					}
				),
				layer.end()
			);

		}

		//	���C���[�ԍ��̏��������ɕ`��
		for (auto& layer : renderers_) {
			for (auto& renderer : layer) {
				auto lender = renderer.lock();
				if (lender && lender->isVisible_) {
					lender->Draw();
				}
			}
		}
	}

	//	���ׂč폜
	void Clear() {
		renderers_.clear();
	}

private:
	//	���C���[�ԍ����C���X�^���X�̃R���N�V�������Q�Ɨp�̐��|�C���^����
	std::vector<std::vector<std::weak_ptr<Drawable>>> renderers_;
};