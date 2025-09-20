#pragma once
#include<memory>

class GameObject;
class Component {
public:
	virtual ~Component() = default;
	virtual void Initialize() {};
	virtual void Update() = 0;
	void SetGameObject(std::shared_ptr<GameObject> a_gameObject) { gameObject_ = a_gameObject; }
	std::shared_ptr<GameObject> GetGameObject() { return gameObject_.lock(); }
protected:
	std::weak_ptr<GameObject> gameObject_;
};
