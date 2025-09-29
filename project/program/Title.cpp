#include "Title.h"
#include"factory_title.h"
#include"filePath.h"
#include"UIClickableComponent.h"
#include"InGame.h"
#include"data_Window.h"

#include"SceneManager.h"

Title::Title()
{

}

//	インスタンスの生成
void Title::Initialize()
{
	//	画面表示に必要なインスタンスの生成
	AddGameObject(FactoryTitle::CreateBG(FilePath::title_bg));

	//	スタートボタンの生成
	createStartButton();
}

void Title::createStartButton()
{
	//	タイトルの決定ボタンを生成
	auto window_size = Vector2Df{ (float)WindowData::m_sceneW,(float)WindowData::m_sceneH };

	auto startButton = std::make_shared<GameObject>();
	auto UIClick = startButton->AddComponent<UIClickComponent>(window_size);

	auto window_size_half = window_size / 2.f;

	startButton->transform_.SetPosition(window_size_half);

	UIClick->SetOnClick([]() {
			SceneManager::Instance().ChangeSceneWithTransition<InGame>();
		}
	);

	AddGameObject(startButton);
}


