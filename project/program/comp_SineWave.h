#pragma once
#include"MonoBehaviour.h"
#include"GameObject.h"
#include"MathUtils.h"
#include"Time.h"

class SineWaveComponent : public MonoBehaviour {
public:
    /// <summary>
    /// 振れ幅、振動数/秒
    /// </summary>
    /// <param name="amplitude"></param>
    /// <param name="frequency"></param>
    SineWaveComponent(float amplitude, float frequency)
        : amplitude_(amplitude), frequency_(frequency), elapsedTime_(0.0f), baseY_(0.0f), initialized_(false) {
    }

    // 毎フレーム呼ばれる更新関数
    void Update()override {
        if (!initialized_) {
            baseY_ = GetGameObject()->transform_.WorldPosition().y; // 初期Y座標を基準に
            initialized_ = true;
        }

        elapsedTime_ += Time::deltaTime();

        float newY = MathUtils::CalcSineWave(baseY_, amplitude_, frequency_, elapsedTime_);
        GetGameObject()->transform_.WorldPosition().x;
        GetGameObject()->transform_.SetPosition({ GetGameObject()->transform_.WorldPosition().x, newY });
    }
private:
    float amplitude_;   // 揺れ幅
    float frequency_;   // 周波数（1秒間に何回揺れるか）
    float elapsedTime_; // 経過時間
    float baseY_;       // 基準Y座標
    bool initialized_;  // 初期座標設定済みか
};