#include "GameOverOverLay.h"
#include"SceneManager.h"
#include"UIClickableComponent.h"
#include"InGame.h"
#include"Title.h"
#include"data_Window.h"
#include"DxlibRap.h"
#include"GetColor.h"
#include"text.h"
#include"Rect.h"
#include"WaveManager.h"

void GameOverOverlay::CreateButtons()
{
    //  リスタートボタン
    auto restartBtn = std::make_shared<GameObject>();

    //  当たり判定のサイズ
    auto restartSize = Vector2Df{ 270, 60 };

    //  当たり判定
    auto restartClick = restartBtn->AddComponent<UIClickComponent>(restartSize);
    //  切り替え処理
    restartClick->SetOnClick([this]() {
        SceneManager::Instance().ChangeScene<InGame>();
        this->isFinish = true;
        });
    //  フラグを一旦折る
    restartBtn->enable_.Set(Flag::Off);
    gameObjects_.push_back(restartBtn);
    //  描画と座標を設定
    auto restartPos = Vector2Df{ (float)WindowData::m_sceneW / 2,(float)WindowData::m_sceneH / 7 * 5 };
    restartBtn->transform_.SetPosition(restartPos);

    auto restartBg = restartBtn->AddComponent<Rect>(
        restartSize, GetColor(255, 255, 255), 0, 11);
    auto restartText = restartBtn->AddComponent<Text>(
        "リスタートする", WHITE, true, 40, 12);

    // Hover時の処理
    restartClick->SetOnHover([restartBg, restartText](bool hovered) {
        if (hovered) {
            restartBg->SetAlpha(80);
            restartText->SetColor(LIGHTYELLOW);
        }
        else {
            restartBg->SetAlpha(0);
            restartText->SetColor(WHITE);
        }
    });

    
    //  タイトルボタン
    auto titleBtn = std::make_shared<GameObject>();
    //  
    auto titleSize = Vector2Df{ 270, 60 };


    //  当たり判定(サイズ設定)
    auto titleClick = titleBtn->AddComponent<UIClickComponent>(titleSize);
    //  切り替え処理
    titleClick->SetOnClick([this]() {
        SceneManager::Instance().ChangeScene<Title>();
        this->isFinish = true;
        });
    //  フラグを一旦折る
    titleBtn->enable_.Set(Flag::Off);
    gameObjects_.push_back(titleBtn);
    //  描画と座標を設定
    auto titlePos = Vector2Df{ (float)WindowData::m_sceneW / 2,(float)WindowData::m_sceneH / 7 * 6 };
    titleBtn->transform_.SetPosition(titlePos);

    auto titleBg = titleBtn->AddComponent<Rect>(
        titleSize, GetColor(255, 255, 255), 0, 11);
    auto titleText = titleBtn->AddComponent<Text>(
        "タイトルに戻る", WHITE, true, 40, 12);

    // Hover時の処理
    titleClick->SetOnHover([titleBg, titleText](bool hovered) {
        if (hovered) {
            titleBg->SetAlpha(80);
            titleText->SetColor(LIGHTYELLOW);
        }
        else {
            titleBg->SetAlpha(0);
            titleText->SetColor(WHITE);        }
        });




    //  撃破数の表示
    auto killCountBtn = std::make_shared<GameObject>();
    //  フラグを一旦折る
    killCountBtn->enable_.Set(Flag::Off);
    gameObjects_.push_back(killCountBtn);
    //  描画と座標を設定
    auto killCountPos = Vector2Df{ (float)WindowData::m_sceneW / 2,(float)WindowData::m_sceneH / 4 * 2 };
    killCountBtn->transform_.SetPosition(killCountPos);
    //  文字列表示
    killCountBtn->AddComponent<Text>(WaveManager::Instance().GetKillCountFormatString(), WHITE, true, 28, 11);


    //  生存時間
    auto TimerBtn = std::make_shared<GameObject>();
    //  フラグを一旦折る
    TimerBtn->enable_.Set(Flag::Off);
    gameObjects_.push_back(TimerBtn);
    //  描画と座標を設定
    auto TimerPos = Vector2Df{ (float)WindowData::m_sceneW / 2,(float)WindowData::m_sceneH / 7 * 3 };
    TimerBtn->transform_.SetPosition(TimerPos);
    //  文字列表示
    std::string time_str = "生存時間: " + WaveManager::Instance().GetElapsedTimeFormatted();
    TimerBtn->AddComponent<Text>(time_str, WHITE, true, 28, 11);

}

GameOverOverlay::GameOverOverlay()
{

}

void GameOverOverlay::Initialize()
{

    // フェード初期化
    fadeAlpha_ = 0;
    state_ = State::FadeIn;

    //  背景作成
    auto bg = std::make_shared<GameObject>();
    bg->transform_.SetPosition({ (float)WindowData::m_sceneW / 2.0f,(float)WindowData::m_sceneH / 2 });
    bg->AddComponent<Rect>(Vector2Df{ (float)WindowData::m_sceneW,(float)WindowData::m_sceneH }, BLACK, fadeAlpha_, 10);
    gameObjects_.push_back(bg);
    bg_ = bg;

    textPos_ = { WindowData::m_sceneW / 2.0f, -100.0f };


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

    auto rect = bg_.lock()->GetComponent<Rect>();
    rect->SetAlpha(this->fadeAlpha_);

} // update

void GameOverOverlay::Render()
{
    //// 下のシーンを暗転させる
    //SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha_);
    //DrawBox(0, 0, WindowData::m_sceneW, WindowData::m_sceneH, GetColor(0, 0, 0), TRUE);
    //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    if (state_ != State::FadeIn) {
        //
        SetFontSize(48);


        // GAME OVER 文字表示
        RapperDxlib::DrawCenterString(textPos_, "GAME OVER", RED);

        SetFontSize(16);

    }
}

