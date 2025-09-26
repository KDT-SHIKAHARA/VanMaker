#pragma once
#include"GameObject.h"

#include<memory>

class EnemyFactory {
public:
	static std::shared_ptr<GameObject> CreateEnemy(int id,int anim_id);
};
