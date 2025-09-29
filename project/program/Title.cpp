#include "Title.h"
#include"factory_title.h"
#include"filePath.h"
#include"UIClickableComponent.h"
#include"InGame.h"
#include"data_Window.h"
#include"comp_SineWave.h"
#include"Image.h"
#include"system_EventBus.h"
#include"BGMSystem.h"

#include"SceneManager.h"

Title::Title()
{

}

Title::~Title()
{
}

//	インスタンスの生成
void Title::Initialize()
{
	//	画面表示に必要なインスタンスの生成
	AddGameObject(FactoryTitle::CreateBG(GH_FilePath::title_bg));

	//	スタートボタンの生成
	createStartButton();

	createTitleLogo();

	EventBus::Instance().Publish(PlayBGMEvent{ SH_FilePath::title_bgm,-1,1 });
	BGMSystem::Instance().SetVolume(1,128);


}

void Title::End()
{
	EventBus::Instance().Publish(StopBGMEvent{ 1 });

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

void Title::createTitleLogo()
{
	auto obj = std::make_shared<GameObject>();
	obj->transform_.SetPosition({ (float)WindowData::m_sceneW / 5.f * 2,(float)WindowData::m_sceneH / 5 * 2 });
	obj->AddComponent<SineWaveComponent>(20,0.5);
	obj->AddComponent<ImageComponent>("data/texture/title/logo.png",0.3f,10,ImageComponent::Pivot::Center, ImageComponent::RenderSpace::Screen);
	AddGameObject(obj);
}


