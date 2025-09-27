#pragma once
#include"singleton.h"

#include<memory>
#include<vector>


class GameObject;
//	生成したインスタンスを格納して、譲渡メソッドが呼ばれたタイミングで
//	Resourceを全てsceneなどの渡す。
class GameObjectQueue : public Singleton<GameObjectQueue> {
	friend class Singleton<GameObjectQueue>;
	GameObjectQueue() = default;
public:
	void Enqueue(std::shared_ptr<GameObject> obj) {
		queues_.push_back(std::move(obj));
	}

	std::vector<std::shared_ptr<GameObject>> Flush() {
		auto temp = std::move(queues_);
		queues_.clear();
		return temp;
	}

	bool empty() {
		return queues_.empty();
	}

protected:
	std::vector<std::shared_ptr<GameObject>> queues_;
};
