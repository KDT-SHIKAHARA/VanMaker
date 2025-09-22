#pragma once
#include"singleton.h"
#include"Resource.h"

#include<string>
#include<unordered_map>
#include<memory>


class SoundLoader : public Singleton<SoundLoader> {
	friend class Singleton<SoundLoader>;
	SoundLoader() = default;
	~SoundLoader() = default;
	std::shared_ptr<Resource> createSound(const std::string& filePath);
public:
	std::shared_ptr<Resource> LoadSound(const std::string& filePath);

private:
	std::unordered_map<std::string, std::shared_ptr<Resource>> sounds_;
};