#include "GameManager.h"
#include <cassert>
#include "Time.h"
#include "InputManager.h"
#include "system_Collision.h"
#include "system_rigidbody.h"
#include "GameObjectManager.h"
#include "system_Renderer.h"

GameManager::GameManager()
	:isRunning_(true),
	 fps_(60,0,0)
{

}

void GameManager::Initialize()
{
	//	Dxlib WindowsAPI&DirectX������ 
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(WindowData::m_windowFlag);
	SetGraphMode(WindowData::m_sceneW, WindowData::m_sceneH, WindowData::m_colorBit);
	SetMainWindowText("NoName");
	SetBackgroundColor(128, 128, 128);

	//	Dxlib ������
	errno_t err = DxLib_Init();
	assert(err != -1);

	//	Dxlib Window�쐬
	SetDrawScreen(DX_SCREEN_BACK);



}

void GameManager::Run()
{


	while (!ProcessMessage() || isRunning_) {
		clsDx();
		ClearDrawScreen();

		fps_.Update();							//	fps.update
		TimeManager::Instance().Update();		//	Time.update
		InputManager::Instance().Update();		//	Input.update
		GameObjectManager::Instance().RemoveDestroyedObjects(); //	GameObject.RemoveDestroyedObjects
		RigidbodySystem::Instance().Update();	//	Rigid.update
		GameObjectManager::Instance().Update();	//	GameObject.update
		CollisionSystem::Instance().Update();	//	Collision.update
		RigidbodySystem::Instance().Move();		//	Rigid.move
		RendererSystem::Instance().Update();	//	Render.update
		fps_.Wait();						//	fps.wait

#ifdef _DEBUG
		fps_.Draw();						//	[debug] fps.render
#endif // _DEBUG


		ScreenFlip();

	}


}

void GameManager::Exit()
{
}
