#pragma once
#include"comp_Rigidbody.h"
#include"singleton.h"

#include<vector>

class RigidbodySystem : public Singleton<RigidbodySystem> {
	friend class Singleton<RigidbodySystem>;
public:
	RigidbodySystem() = default;
	~RigidbodySystem() = default;


	void Update() {

		//  中身が存在しないRigidbodyを削除
		rigidbodies_.erase(std::remove_if(rigidbodies_.begin(), rigidbodies_.end(),[](Rigidbody* rb) 
			{ return rb == nullptr || rb->GetGameObject() == nullptr; }), rigidbodies_.end());

		for(auto& rb : rigidbodies_){
			rb->Update();
		}
	}

	void Move() {
		for (auto& rb : rigidbodies_) {
			rb->Move();
		}
	}

	/// <summary>
	/// Rigidbody オブジェクトを登録します。
	/// </summary>
	/// <param name="a_rigidbody">登録する Rigidbody オブジェクトへのポインタ。</param>
	void RegisterRigidbody(Rigidbody* a_rigidbody) {
		rigidbodies_.push_back(a_rigidbody);
	}

private:
	std::vector<Rigidbody*> rigidbodies_;
};