#pragma once
#include<memory>
#include<vector>
#include<unordered_map>
#include<string>
#include<fstream>
#include<sstream>
#include <stdexcept>

#include"GameData.h"
#include"LoadCsv.h"

/// <summary>
/// IDでデータを管理・検索・取得するためのテンプレートクラス。
/// </summary>
/// <typeparam name="T">管理するデータ型。T型はidメンバーを持つ必要があります。</typeparam>
template<typename T>
class DataTable {
public:

	/// <summary>
	/// 指定されたパスのCSVファイルを読み込みます。
	/// </summary>
	/// <param name="path">CSVファイルのパスを表す文字列。</param>
	void LoadFromCsv(const std::string& path) {
		try
		{
			//	すべての行のデータを文字列として取得
			auto datas_string = LoadCsv::Load(path);

			//	データが存在するだけ読み込む
			for (const auto& data : datas_string) {
				//	格納する構造体
				std::unique_ptr<T> record = std::make_unique<T>();

				//	読込
				parseRecord(data, record.get());

				//	コレクションに追加
				int id = record->id;
				dataMap_[id] = std::move(record);
			}	//	while
		}	//	try
		catch (const std::runtime_error&)
		{
			//	いつか書きます。
			throw;
		}	// catch

	} // void 

	/// <summary>
	/// 指定されたIDに対応するデータを検索し、見つかった場合はポインタを返します。
	/// </summary>
	/// <param name="id">検索するデータのID。</param>
	/// <returns>見つかった場合はデータへのポインタ、見つからない場合はnullptr。</returns>
	const T* findById(int id) const{
		auto it = dataMap_.find(id);
		if (it != dataMap_.end()) {
			return  it->second.get();
		}
		return nullptr;
	}

	//	型によって読み込む内容が違うので特殊化をする↓
	void parseRecord(const std::vector<std::string>& cells, T* record) {
		static_assert(sizeof(T) == -1, "parseRecord must be specialized for this type.");
	}

protected:
	std::unordered_map<int, std::unique_ptr<T>> dataMap_;
};

//	プレイヤーのデータ
template<>
inline void DataTable<PlayerData>::parseRecord(
	const std::vector<std::string>& cells,
	PlayerData* record
) {
	record->id = std::stoi(cells[0]);
	record->name = cells[1];
	record->weaponId = std::stoi(cells[2]);
	record->hp = std::stoi(cells[3]);
	record->speed = std::stof(cells[4]);
	record->expTableId  = std::stoi(cells[5]);
	record->max_invi = std::stof(cells[6]);
	record->size_w_ = std::stof(cells[7]);
	record->size_h_ = std::stof(cells[8]);
}


//	アニメーションのデータ　
template<>
inline void DataTable<AnimData>::parseRecord(
	const std::vector<std::string>& cells,
	AnimData* record
) {
	record->id = std::stoi(cells[0]);
	record->name = cells[1];
	record->filePath = cells[2];
	record->animFirstFrame = std::stoi(cells[3]);
	record->animLastFrame = std::stoi(cells[4]);
	record->layer = std::stoi(cells[5]);
}

//	敵のデータ
template<>
inline void DataTable<EnemyData>::parseRecord(
	const std::vector<std::string>& cells,
	EnemyData* record
) {
	record->id = std::stoi(cells[0]);
	record->sizeTypeId = std::stoi(cells[1]);
	record->hp = std::stoi(cells[2]);
	record->attack = std::stoi(cells[3]);
	record->behaviorId = std::stoi(cells[4]);
	record->dropExpId = std::stoi(cells[5]);
}

template<>
inline void DataTable<EnemySizeData>::parseRecord(
	const std::vector<std::string>& cells,
	EnemySizeData* record
) {
	record->id = std::stoi(cells[0]);
	record->base_width = std::stoi(cells[1]);
	record->base_height = std::stoi(cells[2]);
	record->exrate = std::stof(cells[3]);
}