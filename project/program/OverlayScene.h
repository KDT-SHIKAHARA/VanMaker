#pragma once
#include"flag.h"

class OverlayScene {
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
public:
	Flag isFinish = false;
};