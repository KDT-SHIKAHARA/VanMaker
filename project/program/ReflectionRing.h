#pragma once
#include"WeaponBase.h"

class ReflectionRing : public WeaponBase {
	void create();
public:
	ReflectionRing();

	//	‰Šú‰»
	void Initialize()override;

	//	”­‰Î
	void Fire()override {};

	//	XV
	void Update()override;
};