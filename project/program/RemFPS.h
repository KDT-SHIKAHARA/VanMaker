#pragma once
#include "DxLib.h"
#include <windows.h>

class RemFPS {
private:
    int targetFps_;        // �Œ肵����FPS 0�̏ꍇ��Fps�̌Œ�Ȃ�
    int frameCount_;       // ���ۂ̂P�b�Ԃ̏�����(FPS)
    double measuredFps_;   // ����FPS(�\���p)
    int displayX_, displayY_; // �\�����W

    ULONGLONG startTime_;  // �P�b�Ԋϑ��p�̃��[�v�̊J�n����
    ULONGLONG baseTime_;   // �I��点��\��{���̏I������ (Wait����p)

public:
    RemFPS(int fps = 60, int x = 0, int y = 0)
        : targetFps_(fps), frameCount_(0), measuredFps_(0.0),
        displayX_(x), displayY_(y)
    {
        startTime_ = GetTickCount64();
        baseTime_ = startTime_;
    }

    // --- ����FPS�̌v�� ---
    void Update() {
        //  �X�V��inc
        frameCount_++;

        //  ���ݎ��Ԃ̎擾
        ULONGLONG now = GetTickCount64();

        //  �O��t���[������o�߂�������
        ULONGLONG elapsed = now - startTime_;

        if (elapsed >= 1000) { // 1�b���ƂɍX�V
            measuredFps_ = (frameCount_ * 1000.0) / elapsed;
            frameCount_ = 0;
            startTime_ = now;
        }
    }

    // --- ����FPS�̕`�� ---
    void Draw() const {
        DrawFormatString(displayX_, displayY_, GetColor(255, 255, 255),
            "%.1f fps", measuredFps_);
    }

    // --- FPS�Œ� ---
    void Wait() {
        if (targetFps_ <= 0) return; // ���������[�h

        baseTime_ += 1000 / targetFps_;
        ULONGLONG now = GetTickCount64();

        //  �\�莞�ԑO�Ȃ�ҋ@
        if (baseTime_ > now) {
            Sleep((DWORD)(baseTime_ - now));
        }
        else {
            // �x�����Ă�����␳
            baseTime_ = now;
        }
    }

    // --- FPS�؂�ւ� ---
    void SetTargetFps(int fps) {
        targetFps_ = fps;
        baseTime_ = GetTickCount64(); // �ؑ֎��Ƀ��Z�b�g
    }

    double GetMeasuredFps() const { return measuredFps_; }
};
