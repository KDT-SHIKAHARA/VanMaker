#pragma once
#include"GameObject.h"

#include<memory>

class EnemyFactory {
	static Vector2Df GetSpawnPosition(int margin_length);
public:
	static std::shared_ptr<GameObject> CreateEnemy(int id);
};
