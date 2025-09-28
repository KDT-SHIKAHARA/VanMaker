#include "TimedText.h"
#include "Time.h"
#include "GameObject.h"
#include "DxLib.h"

TextTimed::TextTimed(const std::string& a_draw, const Vector2Df& a_position, float a_displayTime, unsigned int a_color)
	:Drawable(5),draw_(a_draw), position_(a_position), displayTime_(a_displayTime), color_(a_color)
{
}

void TextTimed::Update()
{

	//	‚Ü‚¾Žõ–½‚ª‚ ‚é‚Æ‚«
	if (displayTime_ > 0) {
		//	ŽžŠÔ‚ðŒ¸‚ç‚·
		displayTime_ -= Time::deltaTime();
	}
	//	‚à‚¤‚È‚¢‚Æ‚«
	else {
		//	Ž©‰ó‚ð‚·‚é
		GetGameObject()->isDestory_.Set(Flag::On);
	}

}

void TextTimed::Draw()
{
	DrawStringF(position_.x, position_.y, draw_.c_str(), color_);
}
