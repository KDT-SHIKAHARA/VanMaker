#pragma once
#include"MonoBehaviour.h"
#include"WeaponBase.h"

#include<memory>
#include<vector>
#include<functional>
#include<unordered_map>

/// <summary>
/// ���퐶���̃R���N�V�������Ǘ�����R���|�[�l���g
/// </summary>
class WeaponComponent : public MonoBehaviour {
public:
	WeaponComponent();
	virtual ~WeaponComponent() = default;
	void Update()override;
	void CreateWeapon(int a_id);
protected:
	//	�������\�b�h
	std::unordered_map<int, std::function<std::unique_ptr<WeaponBase>()>> creates_;

	//	�����������퐶���N���X�̃R���N�V����
	std::vector<std::unique_ptr<WeaponBase>> weapons_;
};
