#include "comp_input.h"
#include "InputManager.h"

#include<DxLib.h>
#include<stdexcept>


void InputComponent::Update()
{
	//	ƒNƒŠƒA
	direction_.Clear();
	isMove_ = Flag::Off;

	//	“ü—Í‚É‰‚¶‚ÄˆÚ“®•ûŒü‚ğ‰ÁZ
	//	¶
	if (Input::IsKeyPressed(KEY_INPUT_A)) {
		direction_ += Vector2Df{ -1,0 };
		isMove_ = Flag::On;
	}
	//	‰E
	if (Input::IsKeyPressed(KEY_INPUT_D)) {
		direction_ += Vector2Df{ 1,0 };
		isMove_ = Flag::On;
	}
	//	ã
	if (Input::IsKeyPressed(KEY_INPUT_W)) {
		direction_ += Vector2Df{ 0,-1 };
		isMove_ = Flag::On;
	}
	//	‰º
	if (Input::IsKeyPressed(KEY_INPUT_S)) {
		direction_ += Vector2Df{ 0,1 };
		isMove_ = Flag::On;
	}

}