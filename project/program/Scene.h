#pragma once

class Scene {
public:
	Scene() = default;
	~Scene() = default;
	virtual void Initialize() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
};