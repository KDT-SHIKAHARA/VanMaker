#include "GameManager.h"
#include <cassert>
#include "Time.h"
#include "InputManager.h"
#include "system_Collision.h"
#include "system_rigidbody.h"
#include "GameObjectManager.h"
#include "system_Renderer.h"
#include "SceneManager.h"
#include "Camera.h"
#include "InGame.h"
#include "EventInitializer.h"
#include "loader_Sound.h"
#include "Title.h"
#include "BGMSystem.h"

GameManager::GameManager()
	:isRunning_(true),
	 fps_(60,0,0)
{

}


void GameManager::LoadSoundHandle()
{
	SoundLoader::Instance().LoadSound("data/sound/level/levelUp.MP3");
}

void GameManager::Initialize()
{
	//	Dxlib WindowsAPI&DirectXèâä˙âª 
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(WindowData::m_windowFlag);
	SetGraphMode(WindowData::m_sceneW, WindowData::m_sceneH, WindowData::m_colorBit);
	SetMainWindowText("NoName");
	SetBackgroundColor(128, 128, 128);

	//	Dxlib èâä˙âª
	errno_t err = DxLib_Init();
	assert(err != -1);

	//	Dxlib WindowçÏê¨
	SetDrawScreen(DX_SCREEN_BACK);

	SetMouseDispFlag(TRUE);

	SceneManager::Instance().ChangeScene<Title>();
	SceneManager::Instance().Initialize();

	//	eventÇÃèâä˙âª
	EventInitializer::InitializeEvents();

	//	ÉTÉEÉìÉhÇÃì«Ç›çûÇ›
	LoadSoundHandle();

	BGMSystem::Instance();
}

void GameManager::Run()
{


	while (!ProcessMessage() && isRunning_) {
		clsDx();
		ClearDrawScreen();

		fps_.Update();							//	fps.update
		TimeManager::Instance().Update();		//	Time.update
		InputManager::Instance().Update();		//	Input.update
		SceneManager::Instance().Update();		//	Scene.update
		RigidbodySystem::Instance().Update();	//	Rigid.update
		Camera::Instance().Update();			//	Camera.update
		CollisionSystem::Instance().Update();	//	Collision.update
		RigidbodySystem::Instance().Move();		//	Rigid.move
		RendererSystem::Instance().Update();	//	Render.update
		SceneManager::Instance().Render();		//	Scene.render
		SceneManager::Instance().DestoryGameObjects(); //	Scene.removeDestroyedObjects
		GameObjectRegistry::Instance().Update();	//	GameObject.update

		fps_.Wait();						//	fps.wait

#ifdef _DEBUG
		fps_.Draw();						//	[debug] fps.render
#endif // _DEBUG

		if (Input::IsKeyPressed(KEY_INPUT_ESCAPE) && Input::IsKeyPressed(KEY_INPUT_RETURN)) {
			break;
		}

		ScreenFlip();

	}


}

void GameManager::Exit()
{
}
