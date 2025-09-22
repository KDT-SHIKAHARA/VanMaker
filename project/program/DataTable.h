#pragma once
#include<memory>
#include<vector>
#include<unordered_map>

/// <summary>
/// IDでデータを管理・検索・取得するためのテンプレートクラス。
/// </summary>
/// <typeparam name="T">管理するデータ型。T型はidメンバーを持つ必要があります。</typeparam>
template<typename T>
class DataTable {
public:
	//	データ追加
	void Add(const T& data) {
		dataMap_[data.id] = std::make_unique<T>(data);
	}

	//	IDでデータの検索
	const T* GetById(int id) const {
		auto it = dataMap_.find(id);
		if (it != dataMap_.end()) {
			return it->second.get();
		}
		return nullptr; // 見つからなかった場合はnullptrを返す
	}

	//	全てのデータを取得
	std::vector<const T*> GetAll() const {
		std::vector<const T*> allData;
		for (const auto& pair : dataMap_) {
			allData.push_back(pair.second.get());
		}
		return allData;
	}

protected:
	std::unordered_map<int, std::unique_ptr<T>> dataMap_;
};