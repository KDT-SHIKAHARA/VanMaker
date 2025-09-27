#pragma once
#include"DxLib.h"
#include"vector2d.h"

class RapperDxlib {
public:
	static int DrawExtendGraphFCamera( const Vector2Df& pos1, const Vector2Df& pos2, int GrHandle, int TransFlag);
	static int DrawRotaGraphFCamera(const Vector2Df& pos, const double& ExtRate, const double& Angle, int GrHandle, int TransFlag,int TurnFlag = 0);
	static int DrawBoxAACamera(const Vector2Df& pos1, const Vector2Df& pos2, unsigned int Color, int FillFlag,float LineThickness = 1.0f);
	static int DrawCircleAACamera(const Vector2Df& pos, float radius, int posnum, unsigned int Color, int FillFlag, float LineThickness = 1.0f);
};