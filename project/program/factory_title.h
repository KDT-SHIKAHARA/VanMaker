#pragma once
#include"GameObject.h"
#include"Image.h"

#include<string>
#include<memory>	

class FactoryTitle {
public:
	//	”wŒi‚Ì‰æ‘œì¬
	static std::shared_ptr<GameObject> CreateBG(const std::string& filePath) {
		auto obj = std::make_shared<GameObject>();
		auto img = obj->AddComponent<Image>(0, filePath, Image::Pivot::TopLeft);
		obj->transform_.SetPosition({ 0.0f,0.0f });
		return obj;
	}

	
};

