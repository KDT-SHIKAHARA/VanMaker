#include "GameOverOverLay.h"
#include"SceneManager.h"
#include"UIClickableComponent.h"
#include"InGame.h"
#include"Title.h"

void GameOverOverlay::CreateButtons()
{
    //  リスタートボタン
    auto restartBtn = std::make_shared<GameObject>();
    //  当たり判定
    auto restartClick = restartBtn->AddComponent<UIClickComponent>(Vector2Df{ 500, 60 });
    //  切り替え処理
    restartClick->SetOnClick([this]() {
        SceneManager::Instance().ChangeScene<InGame>();
        this->isFinish = true;
        });
    //  フラグを一旦折る
    restartBtn->enable_.Set(Flag::Off);
    gameObjects_.push_back(restartBtn);
    //  描画と座標を設定


    
    //  タイトルボタン
    auto titleBtn = std::make_shared<GameObject>();
    //  当たり判定(サイズ設定)
    auto titleClick = titleBtn->AddComponent<UIClickComponent>(Vector2Df{ 200, 60 });
    //  切り替え処理
    titleClick->SetOnClick([this]() {
        SceneManager::Instance().ChangeScene<Title>();
        this->isFinish = true;
        });
    //  フラグを一旦折る
    titleBtn->enable_.Set(Flag::Off);
    gameObjects_.push_back(titleBtn);

    //  描画と座標を設定


}

GameOverOverlay::GameOverOverlay()
{

}

void GameOverOverlay::Initialize()
{
    textPos_ = { WindowData::m_sceneW / 2.0f, -100.0f };

    // フェード初期化
    fadeAlpha_ = 0;
    state_ = State::FadeIn;

    // ボタン生成（非表示）
    CreateButtons();
}

void GameOverOverlay::Update()
{
    switch (state_) {
    case State::FadeIn:
        fadeAlpha_ += 8; // フェード速度
        if (fadeAlpha_ >= maxFadeAlpha_ || Input::IsActionTriggered(Action::Select)) {
            fadeAlpha_ = maxFadeAlpha_;
            state_ = State::TextScroll;
        }
        break;

    case State::TextScroll:
        textPos_.y += 4.0f;
        if (textPos_.y >= stopY_ || Input::IsActionTriggered(Action::Select)) {
            textPos_.y = stopY_;
            state_ = State::ShowButtons;
            for (auto& b : gameObjects_) b->enable_.Set(Flag::On);
        }
        break;

    case State::ShowButtons:
        // ボタンが UIClickComponent で自動更新される想定
        for (auto& obg : gameObjects_) {
            obg->Update();
        }
        break;
    }
} // update

void GameOverOverlay::Render()
{
    // 下のシーンを暗転させる
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha_);
    DrawBox(0, 0, WindowData::m_sceneW, WindowData::m_sceneH, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    if (state_ != State::FadeIn) {
        // GAME OVER 文字表示
        DrawString(static_cast<int>(textPos_.x), static_cast<int>(textPos_.y),
            "GAME OVER", GetColor(255, 0, 0));
    }
}

