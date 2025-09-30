#pragma once
#include"OverlayScene.h"
#include"vector2d.h"
#include"data_Window.h"
#include"GameObject.h"
#include"UIClickableComponent.h"


#include<memory>
#include<functional>


class GameOverOverlay : public OverlayScene {

    void CreateButtons();
public:
    GameOverOverlay();
    virtual ~GameOverOverlay();

    void Initialize()override;
    void Update() override;
    void Render() override;
    void RequestFinish() { finishRequested_ = true; }
    bool IsFinishRequested() const { return finishRequested_; }
private:
    enum class State {
        FadeIn,
        TextScroll,
        ShowButtons
    } state_;

    int fadeAlpha_;
    const int maxFadeAlpha_ = 180; // 透過率（暗さ）

    Vector2Df textPos_;
    float stopY_ = WindowData::m_sceneH / 3.0f;

    std::vector<std::weak_ptr<UIClickComponent>> menuButtons_;
    int selectedIndex_ = 0;

    std::weak_ptr<GameObject> bg_;
    bool finishRequested_ = false;
    bool useKeyboard_ = true; // マウス操作があれば false になる
};