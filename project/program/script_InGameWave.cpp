#include "script_InGameWave.h"
#include "WaveManager.h"


void InGameWaveScript::Update()
{
	WaveManager::Instance().Update();
}
