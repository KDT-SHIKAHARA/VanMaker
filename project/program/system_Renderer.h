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
	void RegisterRenderer(Drawable* renderer) {
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
			layer.erase(std::remove_if(layer.begin(), layer.end(),
				[](Drawable* renderer) { return renderer == nullptr || renderer->shared_from_this() == nullptr; }),
				layer.end());
		}

		//	���C���[�ԍ��̏��������ɕ`��
		for (auto& layer : renderers_) {
			for (auto& renderer : layer) {
				if (renderer && renderer->isVisible_) {
					renderer->Draw();
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
	std::vector<std::vector<Drawable*>> renderers_;
};