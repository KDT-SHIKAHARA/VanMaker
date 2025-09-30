#pragma once
#include"system_EventBus.h"
#include"Resource.h"
#include <unordered_map>
#include"loader_Sound.h"
#include"singleton.h"

class BGMSystem :public Singleton<BGMSystem >{
    friend class Singleton<BGMSystem>;

    BGMSystem() {
        EventBus::Instance().Subscribe<PlayBGMEvent>([this](const PlayBGMEvent& e) {
            PlayBGM(e.filepath, e.loopCount, e.handleId);
            });

        EventBus::Instance().Subscribe<StopBGMEvent>([this](const StopBGMEvent& e) {
            StopBGM(e.handleId);
            });
    }

    ~BGMSystem() {
        StopAll(); // DxLib終了前に停止
    }

public:

    void PlayBGM(const std::string& filepath, int loopCount, int handleId) {
        // サウンドリソースを取得（キャッシュ対応）
        auto res = SoundLoader::Instance().LoadSound(filepath);
        if (!res || !res->HasHandle()) return;

        int handle = res->GetHandle();

        int playType = (loopCount == -1) ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
        PlaySoundMem(handle, playType, TRUE); // TRUE は非同期再生用だよ


        if (handleId != -1) {
            handles_[handleId] = res;
        }
        else {
            handles_[nextHandleId_++] = res;
        }
    }

    void StopBGM(int handleId) {
        auto it = handles_.find(handleId);
        if (it != handles_.end() && it->second->HasHandle()) {
            StopSoundMem(it->second->GetHandle());
            handles_.erase(it);
        }
    }

    void StopAll() {
        for (auto& kv : handles_) {
            if (kv.second->HasHandle()) {
                StopSoundMem(kv.second->GetHandle());
            }
        }
        handles_.clear();
    }

    void SetVolume(int handleId, int volume) {
        auto it = handles_.find(handleId);
        if (it != handles_.end() && it->second->HasHandle()) {
            ChangeVolumeSoundMem(volume, it->second->GetHandle());
        }
    }

private:
    std::unordered_map<int, std::shared_ptr<Resource>> handles_; // handleId → Resource
    int nextHandleId_ = 0;
};
