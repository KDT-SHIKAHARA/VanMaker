#pragma once
#include"SceneSclipt.h"
#include"InputManager.h"
#include"SceneManager.h"
#include"PauseScene.h"

class PauseBehaviour : public SceneScript {
public:
	void Update()override {
        // ポーズ判定
        if (Input::IsKeyOn(KEY_INPUT_ESCAPE)) {
            // SceneManager にオーバーレイとして追加
            SceneManager::Instance().CreateOverlay<PauseOverlay>();
        }
	}
};