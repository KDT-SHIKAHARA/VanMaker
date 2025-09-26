#include "DxlibRap.h"
#include "Camera.h"

int RapperDxlib::DrawExtendGraphFCamera(const Vector2Df& pos1, const Vector2Df& pos2, int GrHandle, int TransFlag)
{
    // �J�������S���W
    auto cameraPos = Camera::Instance().GetPosition();
    // �X�N���[�����S�␳
    auto half = Camera::Instance().GetSize() / 2;

    auto drawPos1 = pos1 - cameraPos + half;
    auto drawPos2 = pos2 - cameraPos + half;
    DrawExtendGraphF(drawPos1.x, drawPos1.y, drawPos2.x, drawPos2.y, GrHandle, TransFlag);
	return 0;
}

int RapperDxlib::DrawRotaGraphFCamera(const Vector2Df& pos, const double& ExtRate, const double& Angle, int GrHandle, int TransFlag, int TurnFlag)
{
    // �J�������S���W
    auto cameraPos = Camera::Instance().GetPosition();
    // �X�N���[�����S�␳
    auto half = Camera::Instance().GetSize() / 2;
    auto drewPos = pos - cameraPos + half;
	DrawRotaGraphF(drewPos.x, drewPos.y, ExtRate, Angle, GrHandle, TransFlag, TurnFlag);
    return 0;
}

int RapperDxlib::DrawBoxAACamera(const Vector2Df& pos1, const Vector2Df& pos2, unsigned int Color, int FillFlag, float LineThickness)
{
    //  �J�������W
    const auto& cameraPos = Camera::Instance().GetPosition();

    //  �X�N���[���̍��W�ɕϊ�
    auto half = Camera::Instance().GetSize() / 2.f;
    auto draw1 = pos1 - cameraPos + half;
    auto draw2 = pos2 - cameraPos + half;

    //  �`��
    return DrawBoxAA(draw1.x, draw1.y, draw2.x, draw2.y, Color, FillFlag, LineThickness);
}
