#pragma once


//	ƒtƒ‰ƒO
class Flag {
	bool flag;
public:
	enum {
		On = true,
		Off = false
	};

	Flag(bool arg_flag = false):flag(arg_flag){}
	void Toggle() { flag = !flag; }
	void Set(bool arg_flag) { flag = arg_flag; }
	operator bool()const { return flag; }
};