#pragma once
#include "system_EventBus.h"
#include "Resource.h"
#include "loader_Sound.h"
#include "singleton.h"
#include <vector>
#include <algorithm>

class SESystem : public Singleton<SESystem> {
    friend class Singleton<SESystem>;

    SESystem() {
        // イベント購読
        EventBus::Instance().Subscribe<PlaySEEvent>([this](const PlaySEEvent& e) {
            PlaySE(e.filepath);
            });
    }

    ~SESystem() {
        StopAll();
    }

public:
    // 効果音再生
    void PlaySE(const std::string& filepath) {
        auto res = SoundLoader::Instance().LoadSound(filepath);
        if (!res || !res->HasHandle()) return;

        // 複製ハンドルを作らないと多重再生できない
        int dupHandle = DuplicateSoundMem(res->GetHandle());
        if (dupHandle == -1) return;

        PlaySoundMem(dupHandle, DX_PLAYTYPE_BACK, TRUE);
        activeHandles_.push_back(dupHandle);
    }

    // 終了した効果音のクリーンアップ
    void Update() {
        activeHandles_.erase(
            std::remove_if(activeHandles_.begin(), activeHandles_.end(),
                [](int h) {
                    if (CheckSoundMem(h) == 0) { // 再生終了
                        DeleteSoundMem(h);
                        return true;
                    }
                    return false;
                }),
            activeHandles_.end());
    }

    void StopAll() {
        for (auto h : activeHandles_) {
            DeleteSoundMem(h);
        }
        activeHandles_.clear();
    }

private:
    std::vector<int> activeHandles_; // 再生中ハンドル管理
};