#include "system_Collision.h"
#include "CheckHit.h"
#include"GameObjectManager.h"
#include "Collision.h"

#include<algorithm>


bool CollisionSystem::checkCollision(std::shared_ptr<GameObject> obj1, std::shared_ptr<Collider> colider1, std::shared_ptr<GameObject> obj2, std::shared_ptr<Collider> colider2)
{
	//	ワールド座標の取得
    const auto& pos1 = obj1->transform_.WorldPosition();
    const auto& pos2 = obj2->transform_.WorldPosition();

	//	当たり判定の種類で分岐
	const auto& type1 = colider1->GetColliderType();
	const auto& type2 = colider2->GetColliderType();

	//	タイプによって当たり判定を行う
	if (type1 == ColliderType::Circle && type2 == ColliderType::Circle) {
		auto col1 = std::dynamic_pointer_cast<CircleCollider>(colider1);
		auto col2 = std::dynamic_pointer_cast<CircleCollider>(colider2);
		return CheckHit::CircleCircleFast(pos1, col1->GetRadius(), pos2, col2->GetRadius());
	}
	else if (type1 == ColliderType::Rect && type2 == ColliderType::Rect) {
		auto col1 = std::dynamic_pointer_cast<RectCollider>(colider1);
		auto col2 = std::dynamic_pointer_cast<RectCollider>(colider2);
		return CheckHit::BoxBox(pos1, col1->GetSize(), pos2, col2->GetSize());
	}
	else if (type1 == ColliderType::Circle && type2 == ColliderType::Rect) {
		auto col1 = std::dynamic_pointer_cast<CircleCollider>(colider1);
		auto col2 = std::dynamic_pointer_cast<RectCollider>(colider2);
		return CheckHit::BoxCircle(pos2, col2->GetSize(), pos1, col1->GetRadius());
	}
	else if (type1 == ColliderType::Rect && type2 == ColliderType::Circle) {
		auto col1 = std::dynamic_pointer_cast<RectCollider>(colider1);
		auto col2 = std::dynamic_pointer_cast<CircleCollider>(colider2);
		return CheckHit::BoxCircle(pos1, col1->GetSize(), pos2, col2->GetRadius());
	}

    return false;

}

//	押し戻し処理をする
void CollisionSystem::pushOut(std::shared_ptr<GameObject> obj1, std::shared_ptr<Collider> colider1, std::shared_ptr<GameObject> obj2, std::shared_ptr<Collider> colider2)
{
    auto pos1 = obj1->transform_.WorldPosition();
    auto pos2 = obj2->transform_.WorldPosition();

    auto type1 = colider1->GetColliderType();
    auto type2 = colider2->GetColliderType();

    bool push1 = colider1->isPushed_; // Collider に定義済みのフラグ
    bool push2 = colider2->isPushed_;

    // --- Circle - Circle ---
    if (type1 == ColliderType::Circle && type2 == ColliderType::Circle) {
        auto col1 = std::dynamic_pointer_cast<CircleCollider>(colider1);
        auto col2 = std::dynamic_pointer_cast<CircleCollider>(colider2);

        float r1 = col1->GetRadius();
        float r2 = col2->GetRadius();

        auto diff = pos1 - pos2;
        float dist = diff.GetLength();

        if (dist < r1 + r2 && dist > 0.0001f) {
            float overlap = (r1 + r2) - dist;
            auto pushDir = diff.Normalize();

            if (push1 && push2) {
                pos1 += pushDir * (overlap / 2.0f);
                pos2 -= pushDir * (overlap / 2.0f);
            }
            else if (push1) {
                pos1 += pushDir * overlap;
            }
            else if (push2) {
                pos2 -= pushDir * overlap;
            }
        }
    }

    // --- Rect - Rect (AABB) ---
    else if (type1 == ColliderType::Rect && type2 == ColliderType::Rect) {
        auto col1 = std::dynamic_pointer_cast<RectCollider>(colider1);
        auto col2 = std::dynamic_pointer_cast<RectCollider>(colider2);

        auto size1 = col1->GetSize();
        auto size2 = col2->GetSize();

        float dx = (pos1.x - pos2.x);
        float px = (size1.x / 2 + size2.x / 2) - std::abs(dx);

        float dy = (pos1.y - pos2.y);
        float py = (size1.y / 2 + size2.y / 2) - std::abs(dy);

        if (px > 0 && py > 0) {
            if (px < py) {
                if (push1 && push2) {
                    pos1.x += (dx > 0 ? px / 2 : -px / 2);
                    pos2.x -= (dx > 0 ? px / 2 : -px / 2);
                }
                else if (push1) {
                    pos1.x += (dx > 0 ? px : -px);
                }
                else if (push2) {
                    pos2.x -= (dx > 0 ? px : -px);
                }
            }
            else {
                if (push1 && push2) {
                    pos1.y += (dy > 0 ? py / 2 : -py / 2);
                    pos2.y -= (dy > 0 ? py / 2 : -py / 2);
                }
                else if (push1) {
                    pos1.y += (dy > 0 ? py : -py);
                }
                else if (push2) {
                    pos2.y -= (dy > 0 ? py : -py);
                }
            }
        }
    }

    // --- Circle - Rect ---
    else if (type1 == ColliderType::Circle && type2 == ColliderType::Rect) {
        auto col1 = std::dynamic_pointer_cast<CircleCollider>(colider1);
        auto col2 = std::dynamic_pointer_cast<RectCollider>(colider2);

        float r = col1->GetRadius();
        auto size = col2->GetSize();

        float closestX = std::clamp(pos1.x, pos2.x - size.x / 2, pos2.x + size.x / 2);
        float closestY = std::clamp(pos1.y, pos2.y - size.y / 2, pos2.y + size.y / 2);

        float dx = pos1.x - closestX;
        float dy = pos1.y - closestY;
        float distSq = dx * dx + dy * dy;

        if (distSq < r * r && distSq > 0.0001f) {
            float dist = std::sqrt(distSq);
            float overlap = r - dist;
            float nx = dx / dist;
            float ny = dy / dist;

            if (push1 && push2) {
                pos1.x += nx * (overlap / 2);
                pos1.y += ny * (overlap / 2);
                pos2.x -= nx * (overlap / 2);
                pos2.y -= ny * (overlap / 2);
            }
            else if (push1) {
                pos1.x += nx * overlap;
                pos1.y += ny * overlap;
            }
            else if (push2) {
                pos2.x -= nx * overlap;
                pos2.y -= ny * overlap;
            }
        }
    }
    else if (type1 == ColliderType::Rect && type2 == ColliderType::Circle) {
        // 呼び出し順を逆にして再利用
        pushOut(obj2, colider2, obj1, colider1);
    }

    //  座標の更新
	obj1->transform_.SetWorldPosition(pos1);
	obj2->transform_.SetWorldPosition(pos2);

}

CollisionSystem::CollisionSystem()
{
	rules_ = std::make_unique<CollisionRule>();
	//	当たり判定ルールの追加
}

/// <summary>
/// すべてのGameObjectの当たり判定を行う
/// </summary>
void CollisionSystem::Update()
{
	//	すべてのルールに対して当たり判定を行う
	for (const auto& key : rules_->GetAllRules()) {
        if (key.empty()) continue;
		auto tags = splitTag(key);
		const auto& tag1 = tags.first;
		const auto& tag2 = tags.second;
		//	タグに該当するGameObjectのリストを取得
		auto objList1 = GameObjectRegistry::Instance().FindGameObjectsByTag(Tag::FromString(tag1));
		auto objList2 = GameObjectRegistry::Instance().FindGameObjectsByTag(Tag::FromString(tag2));

		// どちらかのリストが空ならスキップ
        if (objList1.empty() || objList2.empty()) {
            continue;
        }   // if.empty

        //  当たり判定ループ
        for (auto& obj1 : objList1) {
            //  存在判定
            if (!obj1) continue;    
			auto col1 = obj1->GetComponent<Collider>();
            if (!col1) continue;

            for (auto& obj2 : objList2) {
                //  存在判定
                if (!obj2) continue;
				auto col2 = obj2->GetComponent<Collider>();
				if (!col2) continue;

                // 同じオブジェクト同士の当たり判定はスキップ
                if (obj1 == obj2) continue; 
 
				//  当たり判定
                if (checkCollision(obj1, col1, obj2, col2)) {
                    //  押し戻し処理
                    pushOut(obj1, col1, obj2, col2);

                    //  １
					Collision collision1;
                    collision1.other = obj1;
					collision1.collider = col1;
                    
					//  ２
                    Collision collision2;
                    collision2.other = obj2;
                    collision2.collider = col2;

                    //  コールバックの呼び出し
                    obj1->OnCollisionEnter(collision2);
					obj2->OnCollisionEnter(collision1);


				}   //  if.checkCollision
            
            } // for 3
        } // for 2
	} // for 1
} // update
