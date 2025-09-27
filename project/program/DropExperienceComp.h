#pragma once
#include"MonoBehaviour.h"
#include "comp_Health.h"

#include<memory>

//	経験値の生成をするコンポーネント
class DropExperienceComp : public MonoBehaviour {
protected:
	void create();
public:
	DropExperienceComp(int id);
	void Initialize()override;
	void Update()override;

protected:
	std::weak_ptr<Health> hp_;
	int id_;
	bool dropped_ = false;
};