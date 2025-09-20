#pragma once
#include"singleton.h"
#include "data_Window.h"
#include<DxLib.h>
#include"RemFPS.h"

class GameManager : public Singleton<GameManager> {
	friend class Singleton<GameManager>;
	GameManager();
	virtual ~GameManager() = default;
	//	データリソースの読み込み

	//	テクスチャリソースの読み込み
public:
	/// <summary>
	/// ウィンドウの作成と初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ゲームループ
	/// 画面の更新とスクリーンの更新を行っている。
	/// </summary>
	void Run();

	/// <summary>
	/// ウィンドウの削除、リソースの解放
	/// </summary>
	void Exit();
private:
	RemFPS fps_;		//	fpsの固定と表示
	bool isRunning_;	//	ゲームループの実行フラグ true: 実行  false: 終了

};