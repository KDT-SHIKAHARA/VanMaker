#include "TransitionOverlay.h"
#include "data_Window.h"

#include<DxLib.h>

void TransitionOverlay::Update()
{
    if (phase_ == Phase::FadeOut) {
        alpha_ += fadeSpeed_;
        if (alpha_ >= 255) {
            alpha_ = 255;
            // フェードアウト完了 → シーン切り替え
            if (onMidpointChange_) {
                onMidpointChange_();
                onMidpointChange_ = nullptr; // 一度だけ
            }
            phase_ = Phase::FadeIn;
        }
    }
    else if (phase_ == Phase::FadeIn) {
        alpha_ -= fadeSpeed_;
        if (alpha_ <= 0) {
            alpha_ = 0;
            isFinish = true; // 完了
        }
    }
}

void TransitionOverlay::Render()
{
    // 画面全体に半透明の黒を描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
    DrawBox(0, 0, WindowData::m_sceneW, WindowData::m_sceneH, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
