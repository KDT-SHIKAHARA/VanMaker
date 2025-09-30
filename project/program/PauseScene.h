#pragma once
#include "OverlayScene.h"
#include"UIClickableComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Title.h"
#include "InGame.h"
#include "InputManager.h"
#include"Rect.h"
#include"text.h"

#include"system_EventBus.h"
#include"BGMSystem.h"

class PauseOverlay : public OverlayScene {
public:
    PauseOverlay() : selectedIndex_(0) {}

    void Initialize() override {
        // 背景
        auto bg = std::make_shared<GameObject>();
        bg->transform_.SetPosition({ 640, 360 });
        bg->AddComponent<Rect>(Vector2Df{ 1280, 720 }, GetColor(0, 0, 0), 160, 10);
        gameObjects_.push_back(bg);

        // 再開ボタン
        auto resumeBtn = std::make_shared<GameObject>();
        auto resumeClick = resumeBtn->AddComponent<UIClickComponent>(Vector2Df{ 270, 60 });
        resumeClick->SetOnClick([this]() {
            this->isFinish = true; // OverlaySceneを閉じる
            });
        resumeBtn->transform_.SetPosition({ 640, 300 });
        auto resumeText = resumeBtn->AddComponent<Text>("再開する", WHITE, true, 36, 12);
        resumeClick->SetOnHover([resumeText](bool hovered) {
            resumeText->SetColor(hovered ? LIGHTYELLOW : WHITE);
            });
        menuButtons_.push_back(resumeClick);
        gameObjects_.push_back(resumeBtn);

        // タイトルボタン
        auto titleBtn = std::make_shared<GameObject>();
        auto titleClick = titleBtn->AddComponent<UIClickComponent>(Vector2Df{ 270, 60 });
        titleClick->SetOnClick([this]() {
            SceneManager::Instance().ChangeScene<Title>();
            this->isFinish = true;
            });
        titleBtn->transform_.SetPosition({ 640, 400 });
        auto titleText = titleBtn->AddComponent<Text>("タイトルに戻る", WHITE, true, 36, 12);
        titleClick->SetOnHover([titleText](bool hovered) {
            titleText->SetColor(hovered ? LIGHTYELLOW : WHITE);
            });
        menuButtons_.push_back(titleClick);
        gameObjects_.push_back(titleBtn);


    }

    void Update() override {
        // キーボード操作
        if (Input::IsKeyOn(KEY_INPUT_W)) {
            selectedIndex_ = (selectedIndex_ - 1 + menuButtons_.size()) % menuButtons_.size();
        }
        if (Input::IsKeyOn(KEY_INPUT_S)) {
            selectedIndex_ = (selectedIndex_ + 1) % menuButtons_.size();
        }

        // Hover 状態を更新
        for (size_t i = 0; i < menuButtons_.size(); i++) {
            if (auto btn = menuButtons_[i].lock()) {
                btn->ForceHover(i == selectedIndex_);
            }
        }

        // 決定キー
        if (Input::IsKeyOn(KEY_INPUT_RETURN) || Input::IsKeyOn(KEY_INPUT_SPACE)) {
            if (auto btn = menuButtons_[selectedIndex_].lock()) {
                if (btn->GetOnClick()) {
                    btn->GetOnClick()();

                    if (selectedIndex_ == 1) {
                        //  前の音楽の停止
                        EventBus::Instance().Publish(StopBGMEvent{ 2 });

                    }

                }
            }
        }
    }

    void Render()override {

    }

private:
    std::vector<std::weak_ptr<UIClickComponent>> menuButtons_;
    size_t selectedIndex_;
};
