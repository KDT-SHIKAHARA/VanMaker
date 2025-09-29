#pragma once
#include"OverlayScene.h"

#include<functional>


class TransitionOverlay :public OverlayScene {
public:
    TransitionOverlay(std::function<void()> onMidpointChange)
        : onMidpointChange_(std::move(onMidpointChange)) {
    }

    void Update() override;

    void Render() override;

private:
    enum class Phase { FadeOut, FadeIn };
    Phase phase_ = Phase::FadeOut;
    int alpha_ = 0;
    int fadeSpeed_ = 20; // 1ƒtƒŒ[ƒ€‚²‚Æ‚Ì‘Œ¸—Ê
    std::function<void()> onMidpointChange_;
};
