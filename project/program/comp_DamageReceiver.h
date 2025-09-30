#pragma once
#include "MonoBehaviour.h"
#include "comp_Health.h"
#include "Collision.h"
#include "GameObject.h"
#include "comp_Attack.h"
#include "Time.h"
#include "filePath.h"
#include "system_EventBus.h"
#include "BGMSystem.h"

#include<map>
#include <memory>

class DamageReceiver : public MonoBehaviour {
public:
    void Update() override {
        // CT 減少 & 破棄済みオブジェクトの削除
        for (auto it = hitTimer_.begin(); it != hitTimer_.end(); ) {
            if (auto obj = it->first.lock()) {
                if (it->second > 0) it->second -= Time::deltaTime();
                ++it;
            }
            else {
                // 破棄済みは削除
                it = hitTimer_.erase(it);
            }
        }
    }

    void OnCollisionEnter(const Collision& collision) {
        auto attack = collision.other->GetComponent<AttackComp>();
        auto health = GetGameObject()->GetComponentAsBase<Health>();
        if (!attack || !health) return;

        std::weak_ptr<GameObject> key = collision.other; // 個体ごとのキー
        auto it = hitTimer_.find(key);
        if (it != hitTimer_.end() && it->second > 0) return;

        // CT 設定
        hitTimer_[key] = attack->GetCT();

        // ダメージ
        health->Damage(attack->Attack());

        EventBus::Instance().Publish(PlayBGMEvent{ SH_FilePath::hit_se, 1, 6 });
    }

protected:
    // 変更: weak_ptr をキーにして、owner_less で比較
    std::map<std::weak_ptr<GameObject>, double, std::owner_less<std::weak_ptr<GameObject>>> hitTimer_;
};
