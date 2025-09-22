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
/// ID�Ńf�[�^���Ǘ��E�����E�擾���邽�߂̃e���v���[�g�N���X�B
/// </summary>
/// <typeparam name="T">�Ǘ�����f�[�^�^�BT�^��id�����o�[�����K�v������܂��B</typeparam>
template<typename T>
class DataTable {
public:

	/// <summary>
	/// �w�肳�ꂽ�p�X��CSV�t�@�C����ǂݍ��݂܂��B
	/// </summary>
	/// <param name="path">CSV�t�@�C���̃p�X��\��������B</param>
	void LoadFromCsv(const std::string& path) {
			//	���ׂĂ̍s�̃f�[�^�𕶎���Ƃ��Ď擾
			auto datas_string = LoadCsv::Load(path);
			
			//	�f�[�^�����݂��邾���ǂݍ���
			for ( auto& data : datas_string) {
				//	�i�[����\����
				std::unique_ptr<T> record = std::make_unique<T>();

				//	�Ǎ�
				parseRecord(data, record.get());

				//	�R���N�V�����ɒǉ�
				int id = record->id;
				dataMap_[id] = std::move(record);
			}	//	while

	} // void 

	/// <summary>
	/// �w�肳�ꂽID�ɑΉ�����f�[�^���������A���������ꍇ�̓|�C���^��Ԃ��܂��B
	/// </summary>
	/// <param name="id">��������f�[�^��ID�B</param>
	/// <returns>���������ꍇ�̓f�[�^�ւ̃|�C���^�A������Ȃ��ꍇ��nullptr�B</returns>
	const T* findById(int id) const{
		auto it = dataMap_.find(id);
		if (it != dataMap_.end()) {
			return  it->second.get();
		}
		return nullptr;
	}

	//	�^�ɂ���ēǂݍ��ޓ��e���Ⴄ�̂œ��ꉻ�����遫
	void parseRecord(const std::vector<std::string>& cells, T* record) {
		static_assert(sizeof(T) == -1, "parseRecord must be specialized for this type.");
	}

protected:
	std::unordered_map<int, std::unique_ptr<T>> dataMap_;
};

template<>
inline void DataTable<PlayerData>::parseRecord(
	const std::vector<std::string>& cells,
	PlayerData* record
) {
	record->id = std::stoi(cells[0]);
	record->name = cells[1];
	record->filePath = cells[2];
	record->weaponId = std::stoi(cells[3]);
	record->hp = std::stoi(cells[4]);
	record->expTableId = std::stoi(cells[5]);
}