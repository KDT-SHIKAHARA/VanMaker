#pragma once
#include"DxLib.h"
#include"vector2d.h"

#include<string>

class RapperDxlib {
public:
	static int DrawExtendGraphFCamera( const Vector2Df& pos1, const Vector2Df& pos2, int GrHandle, int TransFlag);
	static int DrawRotaGraphFCamera(const Vector2Df& pos, const double& ExtRate, const double& Angle, int GrHandle, int TransFlag,int TurnFlag = 0);
	static int DrawBoxAACamera(const Vector2Df& pos1, const Vector2Df& pos2, unsigned int Color, int FillFlag,float LineThickness = 1.0f);
	static int DrawCircleAACamera(const Vector2Df& pos, float radius, int posnum, unsigned int Color, int FillFlag, float LineThickness = 1.0f);
	static int DrawlineAACamera(const Vector2Df& pos1, const Vector2Df& pos2, unsigned int Color, float Thickness = 1.0f);
	static void DrawLightning(const Vector2Df& start, const Vector2Df& end, int segments, float jaggedness, int color, float thickness);
	static void DrawCenterString(const Vector2Df& pos, const std::string& string, unsigned int Color);
};

