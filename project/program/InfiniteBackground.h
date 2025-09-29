#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"vector2d.h"
#include"Resource.h"

#include<memory>
#include<string>

class InfiniteBackground : public MonoBehaviour, public Drawable {
public:
	InfiniteBackground(const std::string& a_filePath);

	void Update()override;
	void Draw()override;

private:
	std::shared_ptr<Resource> texture_;
	Vector2Df bgSize_;

};