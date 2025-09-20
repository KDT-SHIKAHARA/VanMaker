#pragma once
#include "DxLib.h"
#include <windows.h>

class RemFPS {
private:
    int targetFps_;        // 固定したいFPS 0の場合はFpsの固定なし
    int frameCount_;       // 実際の１秒間の処理回数(FPS)
    double measuredFps_;   // 実測FPS(表示用)
    int displayX_, displayY_; // 表示座標

    ULONGLONG startTime_;  // １秒間観測用のループの開始時間
    ULONGLONG baseTime_;   // 終わらせる予定本来の終了時間 (Wait判定用)

public:
    RemFPS(int fps = 60, int x = 0, int y = 0)
        : targetFps_(fps), frameCount_(0), measuredFps_(0.0),
        displayX_(x), displayY_(y)
    {
        startTime_ = GetTickCount64();
        baseTime_ = startTime_;
    }

    // --- 実測FPSの計測 ---
    void Update() {
        //  更新回数inc
        frameCount_++;

        //  現在時間の取得
        ULONGLONG now = GetTickCount64();

        //  前回フレームから経過した時間
        ULONGLONG elapsed = now - startTime_;

        if (elapsed >= 1000) { // 1秒ごとに更新
            measuredFps_ = (frameCount_ * 1000.0) / elapsed;
            frameCount_ = 0;
            startTime_ = now;
        }
    }

    // --- 実測FPSの描画 ---
    void Draw() const {
        DrawFormatString(displayX_, displayY_, GetColor(255, 255, 255),
            "%.1f fps", measuredFps_);
    }

    // --- FPS固定 ---
    void Wait() {
        if (targetFps_ <= 0) return; // 無制限モード

        baseTime_ += 1000 / targetFps_;
        ULONGLONG now = GetTickCount64();

        //  予定時間前なら待機
        if (baseTime_ > now) {
            Sleep((DWORD)(baseTime_ - now));
        }
        else {
            // 遅延していたら補正
            baseTime_ = now;
        }
    }

    // --- FPS切り替え ---
    void SetTargetFps(int fps) {
        targetFps_ = fps;
        baseTime_ = GetTickCount64(); // 切替時にリセット
    }

    double GetMeasuredFps() const { return measuredFps_; }
};
