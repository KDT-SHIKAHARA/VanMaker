#include "DxlibRap.h"
#include "Camera.h"
#include "random.h"

int RapperDxlib::DrawExtendGraphFCamera(const Vector2Df& pos1, const Vector2Df& pos2, int GrHandle, int TransFlag)
{
    // カメラ中心座標
    auto cameraPos = Camera::Instance().GetPosition();
    // スクリーン中心補正
    auto half = Camera::Instance().GetSize() / 2;

    auto drawPos1 = pos1 - cameraPos + half;
    auto drawPos2 = pos2 - cameraPos + half;
    DrawExtendGraphF(drawPos1.x, drawPos1.y, drawPos2.x, drawPos2.y, GrHandle, TransFlag);
	return 0;
}

int RapperDxlib::DrawRotaGraphFCamera(const Vector2Df& pos, const double& ExtRate, const double& Angle, int GrHandle, int TransFlag, int TurnFlag)
{
    // カメラ中心座標
    auto cameraPos = Camera::Instance().GetPosition();
    // スクリーン中心補正
    auto half = Camera::Instance().GetSize() / 2;
    auto drewPos = pos - cameraPos + half;
	DrawRotaGraphF(drewPos.x, drewPos.y, ExtRate, Angle, GrHandle, TransFlag, TurnFlag);
    return 0;
}

int RapperDxlib::DrawBoxAACamera(const Vector2Df& pos1, const Vector2Df& pos2, unsigned int Color, int FillFlag, float LineThickness)
{
    //  カメラ座標
    const auto& cameraPos = Camera::Instance().GetPosition();

    //  スクリーンの座標に変換
    auto half = Camera::Instance().GetSize() / 2.f;
    auto draw1 = pos1 - cameraPos + half;
    auto draw2 = pos2 - cameraPos + half;

    //  描画
    return DrawBoxAA(draw1.x, draw1.y, draw2.x, draw2.y, Color, FillFlag, LineThickness);
}

int RapperDxlib::DrawCircleAACamera(const Vector2Df& pos, float radius, int posnum, unsigned int Color, int FillFlag, float LineThickness)
{
    //  カメラ座標
    const auto& cameraPos = Camera::Instance().GetPosition();

    //  スクリーンの座標に変換
    auto half = Camera::Instance().GetSize() / 2.f;
    auto draw = pos - cameraPos + half;

    return DrawCircleAA(draw.x, draw.y, radius, posnum, Color, FillFlag, LineThickness);

}

int RapperDxlib::DrawlineAACamera(const Vector2Df& pos1, const Vector2Df& pos2, unsigned int Color, float Thickness)
{
    //  カメラ座標
    const auto& cameraPos = Camera::Instance().GetPosition();

    //  スクリーンの座標に変換
    auto half = Camera::Instance().GetSize() / 2.f;
    auto draw1 = pos1 - cameraPos + half;
    auto draw2 = pos2 - cameraPos + half;

    //  描画
    return DrawLineAA(draw1.x, draw1.y, draw2.x, draw2.y, Color, Thickness);
}

/// <summary>
/// 雷のようにジグザグに線を描く
/// </summary>
/// <param name="start"> 始点 </param>
/// <param name="end">  終点  </param>
/// <param name="segments"> 分割数 </param>
/// <param name="jaggedness"> ジグザクの強さ </param>
/// <param name="color"> 色 </param>
/// <param name="thickness"> 線の太さ </param>
void RapperDxlib::DrawLightning(const Vector2Df& start, const Vector2Df& end, int segments, float jaggedness, int color, float thickness)
{
    std::vector<Vector2Df> points;
    points.push_back(start);

    for (int i = 1; i < segments; i++) {
        float t = static_cast<float>(i) / segments;

        // 補間で直線上の座標を求める
        Vector2Df p = {
            start.x + (end.x - start.x) * t,
            start.y + (end.y - start.y) * t
        };

        // X座標をランダムにずらす（稲妻のギザギザ感）
        float offset = Random::RandomFloat(-jaggedness, jaggedness);
        p.x += offset;

        points.push_back(p);
    }

    points.push_back(end);

    // 線を繋いで描画
    for (size_t i = 0; i < points.size() - 1; i++) {
        RapperDxlib::DrawlineAACamera(points[i], points[i + 1], color, thickness);
    }
}


void RapperDxlib::DrawCenterString(const Vector2Df& pos, const std::string& string, unsigned int Color)
{
    int str = strlen(string.c_str());
    int size = GetDrawStringWidth(string.c_str(),str);
    DrawStringF(pos.x - size / 2, pos.y - GetFontSize() / 2, string.c_str(), Color);
}
