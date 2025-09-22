#pragma once

//	スクリーンごとの処理を行うスクリプトの基底クラス
class SceneScript {
public:
	virtual ~SceneScript() = default;
	virtual void Update() = 0;
};