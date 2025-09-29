#pragma once
#include"GameObject.h"
#include"comp_image.h"
#include"filePath.h"

#include<string>
#include<memory>

class FactoryTitle {
public:
	//	”wŒi‚Ì‰æ‘œì¬
	static std::shared_ptr<GameObject> CreateBG(const std::string& filePath) {
		auto obj = std::make_shared<GameObject>();
		obj->AddComponent<ImageComponent>(filePath, 1.0f, 0, ImageComponent::Pivot::TopLeft, ImageComponent::RenderSpace::Screen);
		obj->transform_.SetPosition({ 0.0f,0.0f });
		return obj;
	}

	
	
};

