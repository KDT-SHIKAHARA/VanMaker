#pragma once

enum class GameObjectTag {
	None,
};

class Tag {
public:
	static std::string GetString(GameObjectTag type_) {
		static const std::unordered_map<GameObjectTag, std::string> typeMap{
			{GameObjectTag::None,"None"},
		};

		return typeMap.at(type_);
	}

	static GameObjectTag FromString(const std::string& str) {
		static const std::unordered_map<std::string, GameObjectTag> strMap{
			{"None",GameObjectTag::None},
		};
		return strMap.at(str);
	}
};