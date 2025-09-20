#pragma once

#include"comp_Collider.h"
#include"CollisionRule.h"
#include"GameObject.h"
#include"Component.h"
#include"singleton.h"

class CollisionSystem : public Singleton<CollisionSystem> {
	friend class Singleton<CollisionSystem>;

	//	�����蔻��
	bool checkCollision(std::shared_ptr<GameObject> obj1,std::shared_ptr<Collider> colider1,
						std::shared_ptr<GameObject> obj2, std::shared_ptr<Collider> colider2);

	//	�����߂�����
	void pushOut(std::shared_ptr<GameObject> obj1, std::shared_ptr<Collider> colider1,
				 std::shared_ptr<GameObject> obj2, std::shared_ptr<Collider> colider2);


	//	: �ŕ�����𕪊�����
	std::pair<std::string, std::string> splitTag(const std::string& key) {
		//	������̌������ĕ������̃C���f�b�N�X�̎擾
		auto pos = key.find(":");
		return { key.substr(0,pos),key.substr(pos + 1) };
	}


public:
	CollisionSystem();
	~CollisionSystem() = default;
	void Update();

private:
	std::unique_ptr<CollisionRule> rules_;	//	�����蔻�胋�[��
};