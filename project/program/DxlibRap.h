#pragma once
#include"DxLib.h"
#include"vector2d.h"

class RapperDxlib {
public:
	static int DrawExtendGraphFCamera( const Vector2Df& pos1, const Vector2Df& pos2, int GrHandle, int TransFlag);
	static int DrawRotaGraphFCamera(const Vector2Df& pos, const double& ExtRate, const double& Angle, int GrHandle, int TransFlag,int TurnFlag = 0);

};