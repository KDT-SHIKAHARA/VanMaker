#pragma once
#include"MonoBehaviour.h"
#include"Drawable.h"
#include"Resource.h"
#include"vector2d.h"
#include"flag.h"

#include<string>

class ImageComponent : public MonoBehaviour, public Drawable {
public:
	//	基準座標
	enum class Pivot {
		TopLeft,
		Center
	};

	//	
	enum class RenderSpace {
		World,
		Screen
	};

	ImageComponent(const std::string& filePath, float a_exRate,int a_layer, ImageComponent::Pivot a_pivot = ImageComponent::Pivot::Center, RenderSpace a_renderSpace = RenderSpace::World);
	void Update()override;
	void Draw()override;


	//	アクセサ
	void SetAngle(float a_anble) { angle_ = a_anble; }
	void AddAngle(float a_anble) { angle_ += a_anble; }

	RenderSpace GetRenderSpace()const {
		return renderSpace_;
	}
	
protected:

	//	画像のサイズ
	Vector2Df size_;

	//	画像リソース
	std::shared_ptr<Resource> texture_;

	//	各縮率
	float exRate_;

	//	回転
	float angle_;

	//	ピポット
	Pivot pivot_;

public:
	//	左右判定
	Flag isTurn_;

	//	透過フラグ
	Flag isTrans_;

	RenderSpace  renderSpace_;
};



