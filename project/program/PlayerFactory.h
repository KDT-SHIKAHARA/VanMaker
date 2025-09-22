#pragma once
#include"GameObject.h"

#include<memory>


class PlayerFactory {
	public:
	static std::shared_ptr<GameObject> CreatePlayer();
};