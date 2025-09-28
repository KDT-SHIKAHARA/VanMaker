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

		rigidbodies_.erase(
			std::remove_if(
				rigidbodies_.begin(),
				rigidbodies_.end(),
				[](const std::weak_ptr<Rigidbody>& rb) {
					return rb.expired();
				}
			),
			rigidbodies_.end()
		);

		for(auto& rb : rigidbodies_){
			auto r = rb.lock();
			r->Update();
		}
	}

	void Move() {
		for (auto& rb : rigidbodies_) {
			auto r = rb.lock();
			r->Move();
		}
	}

	/// <summary>
	/// Rigidbody オブジェクトを登録します。
	/// </summary>
	/// <param name="a_rigidbody">登録する Rigidbody オブジェクトへのポインタ。</param>
	void RegisterRigidbody(std::shared_ptr<Rigidbody> a_rigidbody) {
		rigidbodies_.push_back(a_rigidbody);
	}

private:
	std::vector<std::weak_ptr<Rigidbody>> rigidbodies_;
};