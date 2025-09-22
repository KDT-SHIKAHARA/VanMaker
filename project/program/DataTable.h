#pragma once
#include<memory>
#include<vector>
#include<unordered_map>

/// <summary>
/// ID�Ńf�[�^���Ǘ��E�����E�擾���邽�߂̃e���v���[�g�N���X�B
/// </summary>
/// <typeparam name="T">�Ǘ�����f�[�^�^�BT�^��id�����o�[�����K�v������܂��B</typeparam>
template<typename T>
class DataTable {
public:
	//	�f�[�^�ǉ�
	void Add(const T& data) {
		dataMap_[data.id] = std::make_unique<T>(data);
	}

	//	ID�Ńf�[�^�̌���
	const T* GetById(int id) const {
		auto it = dataMap_.find(id);
		if (it != dataMap_.end()) {
			return it->second.get();
		}
		return nullptr; // ������Ȃ������ꍇ��nullptr��Ԃ�
	}

	//	�S�Ẵf�[�^���擾
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