#pragma once
#include"singleton.h"
#include"Resource.h"

#include<string>
#include<unordered_map>
#include<memory>

class TextureLoader : public Singleton<TextureLoader> {
	friend class Singleton<TextureLoader>;
	TextureLoader() = default;
	~TextureLoader() = default;

	std::shared_ptr<Resource> createTexture(const std::string& filePath);
public:
	std::shared_ptr<Resource> LoadTexture(const std::string& filePath);
private:
	std::unordered_map<std::string, std::shared_ptr<Resource>> textures_;
};
