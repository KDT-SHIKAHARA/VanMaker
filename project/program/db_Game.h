#pragma once
#include"singleton.h"


/// �Q�[���S�̂̃f�[�^�x�[�X
class GameDataBase : public Singleton<GameDataBase> {
	friend class Singleton<GameDataBase>;
	GameDataBase() = default;
	~GameDataBase() = default;
public:

};