#include<DxLib.h>
#include"GameManager.h"

//	ƒƒCƒ“ƒ‹[ƒv
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	GameManager::Instance().Initialize();
	GameManager::Instance().Run();
	GameManager::Instance().Exit();
}
