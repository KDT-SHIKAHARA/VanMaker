#include "InputManager.h"
#include "DxLib.h"

InputManager::InputManager() {
	m_action[Action::Select][Device::Pad] = {PAD_INPUT_1};
	m_action[Action::Select][Device::Keyboard] = { KEY_INPUT_RETURN};
}

void InputManager::Update()
{
	m_prevKeyState = m_keyStates;	//	前回入力状態保持
	GetHitKeyStateAll(m_keyStates.data());	//	全入力状態取得

	m_prevMouseState = m_mouseState;	//	前回入力保持
	m_mouseState = GetMouseInput();	//	全入力取得

	m_mouseWheel = GetMouseWheelRotVol();	//	マウスホイールの入力取得
	GetMousePoint(&m_mouse.x, &m_mouse.y);	//	マウス座標取得

	m_prevPadState = m_padState;	//	前回入力保持
	if (GetJoypadNum() > 0) m_padState = GetJoypadInputState(DX_INPUT_PAD1);	//	padが繋がっているときだけ全取得

	//	現在の入力デバイス判定
	if (m_padState != 0) m_currentDevice = Device::Pad;
	else if (m_mouseState != 0) m_currentDevice = Device::Mouse;
	else if (anyKey()) m_currentDevice = Device::Keyboard;

}

bool InputManager::IsKeyOn(int a_keyCode) const
{
	return m_keyStates[a_keyCode] && !m_prevKeyState[a_keyCode];
}

bool InputManager::IsKeyPressed(int a_keyCode) const
{
	return m_keyStates[a_keyCode];
}

bool InputManager::IsMouseOn(int a_mouseCode) const
{
	return (m_mouseState & a_mouseCode) && !(m_prevMouseState & a_mouseCode);
}

bool InputManager::IsMousePressed(int a_mouseCode) const
{
	return (m_mouseState & a_mouseCode) != 0;
}

bool InputManager::IsPadOn(int a_padCode) const
{
	return (m_padState & a_padCode) && !(m_prevPadState & a_padCode);
}

bool InputManager::IsPadPressed(int a_padCode) const
{
	return (m_padState & a_padCode) != 0;
}

int InputManager::GetMouseScroll() const
{
	return m_mouseWheel;
}

Vector2Di InputManager::GetMousePos() const
{
	return m_mouse;
}


bool InputManager::IsActionTriggered(Action a_action) const
{
	// アクションに関連する入力デバイスとキーコードを取得
	const auto& actionBinding = m_action.at(a_action);

	for (const auto& [device, keyCodes] : actionBinding)
	{
		// 入力デバイスごとにチェック
		for (int keyCode : keyCodes)
		{
			switch (device)
			{
			case Device::Keyboard:
				// キーが押された瞬間をチェック
				if (IsKeyOn(keyCode)) return true;
				break;

			case Device::Mouse:
				// マウスが押された瞬間をチェック
				if (IsMouseOn(keyCode)) return true;
				break;

			case Device::Pad:
				// ゲームパッドが押された瞬間をチェック
				if (IsPadOn(keyCode)) return true;
				break;
			}
		}
	}
	return false; 
}

bool InputManager::IsActionPressed(Action a_action) const
{
	// アクションに関連する入力デバイスとキーコードを取得
	const auto& actionBinding = m_action.at(a_action);

	for (const auto& [device, keyCodes] : actionBinding)
	{
		// 入力デバイスごとにチェック
		for (int keyCode : keyCodes)
		{
			switch (device)
			{
			case Device::Keyboard:
				// キーが押され続けているかチェック
				if (IsKeyPressed(keyCode)) return true;
				break;

			case Device::Mouse:
				// マウスが押され続けているかチェック
				if (IsMousePressed(keyCode)) return true;
				break;

			case Device::Pad:
				// ゲームパッドが押され続けているかチェック
				if (IsPadPressed(keyCode)) return true;
				break;
			}
		}
	}

	return false;  // どのデバイスでもアクションが発生していない
}
