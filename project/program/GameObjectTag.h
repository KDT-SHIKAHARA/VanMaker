#pragma once

enum class GameObjectTag {
	None,
	Player,
	Enemy,
	Weapon,
	Exp,
};

class Tag {
public:
	static std::string GetString(GameObjectTag type_) {
		static const std::unordered_map<GameObjectTag, std::string> typeMap{
			{GameObjectTag::None,"None"},
			{ GameObjectTag::Player,"Player"},
			{ GameObjectTag::Enemy,"Enemy"},
			{ GameObjectTag::Weapon,"Weapon"},
			{ GameObjectTag::Exp,"Exp"},

		};

		return typeMap.at(type_);
	}

	static GameObjectTag FromString(const std::string& str) {
		static const std::unordered_map<std::string, GameObjectTag> strMap{
			{"None",GameObjectTag::None},
			{"Player",GameObjectTag::Player},
			{"Enemy",GameObjectTag::Enemy},
			{"Weapon",GameObjectTag::Weapon},
			{"Exp",GameObjectTag::Exp},
		};
		return strMap.at(str);
	}
};