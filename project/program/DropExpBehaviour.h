#pragma once
#include"MonoBehaviour.h"

class DropExpBehaviour : public MonoBehaviour {
public:
	DropExpBehaviour(int a_dropExp)
		:dropExp(a_dropExp)
	{ }
	virtual ~DropExpBehaviour() = default;

	void Update()override{}

	int GetDropExp()const { return dropExp; }
protected:
	int dropExp = 0;

};
