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
		try
		{
			//	���ׂĂ̍s�̃f�[�^�𕶎���Ƃ��Ď擾
			auto datas_string = LoadCsv::Load(path);

			//	�f�[�^�����݂��邾���ǂݍ���
			for (const auto& data : datas_string) {
				//	�i�[����\����
				std::unique_ptr<T> record = std::make_unique<T>();

				//	�Ǎ�
				parseRecord(data, record.get());

				//	�R���N�V�����ɒǉ�
				int id = record->id;
				dataMap_[id] = std::move(record);
			}	//	while
		}	//	try
		catch (const std::runtime_error&)
		{
			//	���������܂��B
			throw;
		}	// catch

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

//	�v���C���[�̃f�[�^
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


//	�A�j���[�V�����̃f�[�^�@
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

template<>
inline void DataTable<ImageData>::parseRecord(
	const std::vector<std::string>& cells,
	ImageData* record
) {
	record->id = std::stoi(cells[0]);
	record->filePath = cells[1];
	record->exRate = std::stof(cells[2]);
	record->layer = std::stoi(cells[3]);
}


//	�G�̃f�[�^
template<>
inline void DataTable<EnemyData>::parseRecord(
	const std::vector<std::string>& cells,
	EnemyData* record
) {
	record->id = std::stoi(cells[0]);
	record->sizeTypeId = std::stoi(cells[1]);
	record->hp = std::stoi(cells[2]);
	record->attack = std::stoi(cells[3]);
	record->coolTime_ = std::stof(cells[4]);
	record->behaviorId = std::stoi(cells[5]);
	record->dropExpId = std::stoi(cells[6]);
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

template<>
inline void DataTable<WeaponData>::parseRecord(
	const std::vector<std::string>& cells,
	WeaponData* record
) {
	record->id = std::stoi(cells[0]);
	record->name = cells[1];
	record->width = std::stof(cells[2]);
	record->height = std::stof(cells[3]);
	record->radius = std::stof(cells[4]);
	record->max_ct = std::stof(cells[5]);
	record->attack = std::stoi(cells[6]);
	record->slip_ct = std::stof(cells[7]);
	record->num = std::stoi(cells[8]);
	record->textureID = std::stoi(cells[9]);
}