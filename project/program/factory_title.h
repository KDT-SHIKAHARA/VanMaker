#pragma once
#include"GameObject.h"

#include<string>
#include<memory>	

class FactoryTitle {
public:
	//	�w�i�̉摜�쐬
	static std::shared_ptr<GameObject> CreateBG(const std::string& filePath) {
		auto obj = std::make_shared<GameObject>();
		obj->transform_.SetPosition({ 0.0f,0.0f });
		return obj;
	}

	
};

