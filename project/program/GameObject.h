#pragma once
#include<memory>
#include<type_traits>
#include<typeindex>
#include<unordered_map>
#include<vector>


#include"Component.h"
#include"MonoBehaviour.h"
#include"Transform.h"
#include"flag.h"
#include"GameObjectTag.h"


class GameObject : public std::enable_shared_from_this<GameObject> {
	using Comp_map = std::unordered_map<std::type_index, std::shared_ptr<Component>>;
	using Monobehaviours = std::vector<MonoBehaviour*>;
public:
	GameObject() = default;
	~GameObject() = default;
	
	void Update() {
		// MonoBehaviour��Update���Ăяo��
		for(auto& mb : monoBehaviours_){
			if(mb) mb->Update();
		}
	}
	
	//	�����蔻�肪���������Ƃ��ɌĂяo�����
	void OnCollisionEnter(const Collision& collision) {
		for (auto& mb : monoBehaviours_) {
			if (mb) mb->OnCollisionEnter(collision);
		}
	}

	template<typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);
	
	template<typename T>
	std::shared_ptr<T> GetComponent();
	
	template<typename T>
	bool HasComponent()const;




public:
	Transform transform_;	//	���W�A��]�A�X�P�[��
	GameObjectTag tag_ = GameObjectTag::None;	//	Gameobject�̃^�O
	Flag isDestory_ = false;	//	�폜�t���O
private:
	Comp_map components_;	//	�R���|�[�l���g�̊i�[�}�b�v
	Monobehaviours monoBehaviours_;	//	�X�V�����Monobehaviour�̊i�[
};

template<typename T, typename ...Args>
inline std::shared_ptr<T> GameObject::AddComponent(Args && ...args)
{
	//	component�̐���
	//	std::forward�ŉE�Ӓl�Ȃ�move�A���Ӓl�Ȃ�R�s�[������
	auto comp = std::make_shared<T>(std::forward<Args>(args)...);

	//	�t�^����component��GameObject�������ɂ���B
	comp->SetGameObject(shared_from_this());

	//	�X�^�[�g���\�b�h
	comp->Initialize();

	//	T�^�Ɠ����L�[�̌^�̒��g�ɓ����B(���łɂ���΃��Z�b�g�����)
	components_[std::type_index(typeid (T))] = comp;


	//	Monobehaviour�Ȃ�GameObject��Update�����悤�ɓo�^
	if (auto mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
		monoBehaviours_.push_back(mb);
	}

	//	�w�肵���^�̃R���|�[�l���g��shared_ptr��Ԃ�
	return comp;
}

/// <summary>
/// GameObject�Ɋi�[����Ă���w��^�̃R���|�[�l���g���擾
/// </summary>
/// <typeparam name="T">�擾�������R���|�[�l���g�̌^�B</typeparam>
/// <returns>�w��^T�̃R���|�[�l���g�ւ�std::shared_ptr�B���݂��Ȃ��ꍇ��nullptr��Ԃ��܂��B</returns>
template<typename T>
inline std::shared_ptr<T> GameObject::GetComponent()
{
	//	�������āA�C�e���[�^���i�[ �����Ȃ炻�̏ꏊ�̃C�e���[�^�A���s�Ȃ�.end��Ԃ�
	auto ite = components_.find(std::type_index(typeid(T)));
	//	�����ɐ������Ă��邩�𔻒�
	if (ite != components_.end()) {
		//	���N���X�^����h���^�Ƀ|�C���^��ϊ�����B
		return std::static_pointer_cast<T>(ite->second);
	}
	//	�Ȃ����nullptr��Ԃ��āAif���Ȃǂ�false�ɂȂ�悤�ɂ���
	return nullptr;

}


/// <summary>
/// �w�肵���^�̃R���|�[�l���g�����݂��邩�ǂ����𔻒�
/// </summary>
/// <typeparam name="T">���肷��R���|�[�l���g�̌^�B</typeparam>
/// <returns>�w�肵���^�̃R���|�[�l���g�����݂���ꍇ�� true�A���݂��Ȃ��ꍇ�� false �B</returns>
template<typename T>
inline bool GameObject::HasComponent() const
{
	//	�������ăq�b�g������true�A���s�Ȃ�false��Ԃ�
	auto ite = components_.find(std::type_index(typeid(T)));
	if (ite != components_.end()) {
		return true;
	}
	return false;

}
