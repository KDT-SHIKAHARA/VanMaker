#include "comp_animation.h"
#include "GameObject.h"

void AnimationComp::AddAnim(const std::string& a_AnimKey, const std::string& a_filePath, int a_firstFrame, int a_lastFrame, float a_duration, float exRate, Anim2D::PlayMode a_mode)
{
	//	インスタンス生成
	auto anim2d = std::make_unique<Anim2D>();
	anim2d->LoadFrames(a_filePath, a_firstFrame, a_lastFrame, a_duration, exRate, a_mode);
	currentAnimKey_ = a_AnimKey;
	animations_[a_AnimKey] = std::move(anim2d);
}

void AnimationComp::Update()
{
	if (!currentAnimKey_.empty()) {
		animations_[currentAnimKey_]->Update();
		animations_[currentAnimKey_]->isFlip_.Set(trans_);
	}
}

void AnimationComp::Draw()
{
	if (!currentAnimKey_.empty()) {
		const auto& position = GetGameObject()->transform_.WorldPosition();
		animations_[currentAnimKey_]->Render(position);
	}
}

void AnimationComp::SetAnimKey(const std::string& a_animKey)
{
	if (currentAnimKey_ == a_animKey) return;

	//	キー検索して存在しないキーなら変更できないようにする
	auto it = animations_.find(a_animKey);
	if (it != animations_.end()) {
		animations_[currentAnimKey_]->Reset();
		currentAnimKey_ = a_animKey;
	}

}

