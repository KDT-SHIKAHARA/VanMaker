#pragma once
#include<string>

class PlayerDataLoader {
	PlayerDataLoader() = default;
	~PlayerDataLoader() = default;

public:
	struct CsvData
	{
		int id;				//	�L������id
		std::string name;	//	���O
		std::string filePath;	//	�摜�t�@�C���p�X
		int weaponId;	//	�����id
		int hp;			//	�̗͂̍ő�l
		int expId;		//	�o���l�e�[�u����id
	}; // struct



};	//	class