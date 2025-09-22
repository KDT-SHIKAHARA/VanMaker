#pragma once
#include<memory>


class GameObject;
class Collider;
struct Collision
{
	std::shared_ptr<GameObject> other;	//	どのオブジェクトが当たったかわかるように
	std::shared_ptr<Collider> collider;	//	部位ごとに分ける場合どれにあたったかわかるように
	//	必要な情報が増える場合はここに追加する
};