#pragma once
#include"WeaponBase.h"

class KnifeWeapon : public WeaponBase {
	void create();
public:
	virtual void Initialize()override;
	virtual void Fire() override {};
	virtual void Update() override;

private:

};