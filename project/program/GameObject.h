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
		// MonoBehaviourのUpdateを呼び出す
		for(auto& mb : monoBehaviours_){
			if(mb) mb->Update();
		}
	}
	
	//	当たり判定が発生したときに呼び出される
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
	Transform transform_;	//	座標、回転、スケール
	GameObjectTag tag_ = GameObjectTag::None;	//	Gameobjectのタグ
	Flag isDestory_ = false;	//	削除フラグ
private:
	Comp_map components_;	//	コンポーネントの格納マップ
	Monobehaviours monoBehaviours_;	//	更新されるMonobehaviourの格納
};

template<typename T, typename ...Args>
inline std::shared_ptr<T> GameObject::AddComponent(Args && ...args)
{
	//	componentの生成
	//	std::forwardで右辺値ならmove、左辺値ならコピーをする
	auto comp = std::make_shared<T>(std::forward<Args>(args)...);

	//	付与したcomponentのGameObjectを自分にする。
	comp->SetGameObject(shared_from_this());

	//	スタートメソッド
	comp->Initialize();

	//	T型と同じキーの型の中身に入れる。(すでにあればリセットされる)
	components_[std::type_index(typeid (T))] = comp;


	//	MonobehaviourならGameObjectでUpdateされるように登録
	if (auto mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
		monoBehaviours_.push_back(mb);
	}

	//	指定した型のコンポーネントのshared_ptrを返す
	return comp;
}

/// <summary>
/// GameObjectに格納されている指定型のコンポーネントを取得
/// </summary>
/// <typeparam name="T">取得したいコンポーネントの型。</typeparam>
/// <returns>指定型Tのコンポーネントへのstd::shared_ptr。存在しない場合はnullptrを返します。</returns>
template<typename T>
inline std::shared_ptr<T> GameObject::GetComponent()
{
	//	検索して、イテレータを格納 成功ならその場所のイテレータ、失敗なら.endを返す
	auto ite = components_.find(std::type_index(typeid(T)));
	//	検索に成功しているかを判定
	if (ite != components_.end()) {
		//	基底クラス型から派生型にポインタを変換する。
		return std::static_pointer_cast<T>(ite->second);
	}
	//	なければnullptrを返して、if分などでfalseになるようにする
	return nullptr;

}


/// <summary>
/// 指定した型のコンポーネントが存在するかどうかを判定
/// </summary>
/// <typeparam name="T">判定するコンポーネントの型。</typeparam>
/// <returns>指定した型のコンポーネントが存在する場合は true、存在しない場合は false 。</returns>
template<typename T>
inline bool GameObject::HasComponent() const
{
	//	検索してヒットしたらtrue、失敗ならfalseを返す
	auto ite = components_.find(std::type_index(typeid(T)));
	if (ite != components_.end()) {
		return true;
	}
	return false;

}
