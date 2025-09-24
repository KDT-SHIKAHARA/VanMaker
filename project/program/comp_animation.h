#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"Anim2D.h"

#include<string>
#include<unordered_map>
#include<memory>


class AnimationComp : public Drawable, public MonoBehaviour {
public:
	AnimationComp(int a_layer)
		:Drawable(a_layer){ }
	void AddAnim(const std::string& a_AnimKey,const std::string& a_filePath,int a_firstFrame,int a_lastFrame
		,float a_duration = 0.2,float exRate = 2.0f,Anim2D::PlayMode a_mode = Anim2D::PlayMode::Loop);
	void Update()override;
	void Draw()override;

	//	アニメーションのキーを設定
	void SetAnimKey(const std::string& a_animKey);

	//	再生

	//	停止

	//	中断

private:
	std::unordered_map<std::string, std::unique_ptr<Anim2D>> animations_;
	std::string currentAnimKey_;
};