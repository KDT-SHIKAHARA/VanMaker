#pragma once
#include<unordered_map>
#include<unordered_set>
#include<array>

#include"ActionMap.h"
#include"singleton.h"
#include"vector2d.h"

class InputManager : public Singleton<InputManager> {
	friend class Singleton<InputManager>;
	InputManager();
	virtual ~InputManager() = default;

	/// <summary>
	/// 入力種別
	/// </summary>
	enum class Device {
		Keyboard,
		Mouse,
		Pad,
	};

	//	入力種別とキーコードのバインド	K = 入力種別 V= キーコードリスト
	using InputBinding = std::unordered_map<Device, std::unordered_set<int>>;
	//	アクションとバインドのグループ化	K = アクション種別 V = InputBinding;
	using ActionList = std::unordered_map<Action, InputBinding>;

	//	キー入力判定
	bool anyKey()const {
		for (auto key : m_keyStates) {
			if (key) return true;
		}
		return false;
	}


public:
	//	全体更新
	void Update();

	//	入力取得系
	bool IsKeyOn(int a_keyCode)const;
	bool IsKeyPressed(int a_keyCode)const;
	bool IsMouseOn(int a_mouseCode)const;
	bool IsMousePressed(int a_mouseCode)const;
	bool IsPadOn(int a_padCode)const;
	bool IsPadPressed(int a_padCode)const;
	int GetMouseScroll()const;

	//	マウス座標
	Vector2Di GetMousePos()const;

	//	アクションに対して入力があるかどうかを判定する
	bool IsActionTriggered(Action a_action)const;
	bool IsActionPressed(Action a_action)const;
private:
	Device m_currentDevice = Device::Keyboard;			//	現在の入力デバイス
	int m_mouseState = 0, m_prevMouseState = 0;			//	マウス入力状態用
	int m_padState = 0, m_prevPadState = 0;				//	pad入力状態用
	Vector2Di m_mouse;									//	マウス座標
	int m_mouseWheel = 0;									//	マウスホイールの回転量
	std::array<char, 256> m_keyStates, m_prevKeyState;	//	キー入力状態用
	ActionList m_action;								//	アクションマップ
};


/// <summary>
/// 入力管理クラスのアクセス用のラッパー
/// </summary>
class Input {
public:
	static bool IsKeyOn(int a_keyCode) { return InputManager::Instance().IsKeyOn(a_keyCode); };
	static bool IsKeyPressed(int a_keyCode) { return InputManager::Instance().IsKeyPressed(a_keyCode); };
	static bool IsMouseOn(int a_mouseCode) { return InputManager::Instance().IsMouseOn(a_mouseCode); };
	static bool IsMousePressed(int a_mouseCode) { return InputManager::Instance().IsMousePressed(a_mouseCode); };
	static bool IsPadOn(int a_padCode) { return InputManager::Instance().IsPadOn(a_padCode); };
	static bool IsPadPressed(int a_padCode) { return InputManager::Instance().IsPadPressed(a_padCode); };
	static int GetMouseScroll() { return InputManager::Instance().GetMouseScroll(); };
	static Vector2Di GetMousePos() { return InputManager::Instance().GetMousePos(); };
	static bool IsActionTriggered(Action a_action) { return InputManager::Instance().IsActionTriggered(a_action); };
	static bool IsActionPressed(Action a_action) { return InputManager::Instance().IsActionPressed(a_action); };

};
