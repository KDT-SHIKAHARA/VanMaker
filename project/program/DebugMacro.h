#pragma once


//	デバックフラグ管理
struct DebugFlag
{
//	デバック中のみ

#ifdef _DEBUG
	//	プレイヤーの無敵
	static constexpr bool PlayerInvi = true;

	//	敵の体力の表示
	static constexpr bool EnemyDrawHpBar = true;

	//	当たり判定の可視化
	static constexpr bool DrawCollider = true;

#else
//	フラグの無効化
	static constexpr bool PlayerInvi = false;
	static constexpr bool EnemyDrawHpBar = false;
	static constexpr bool DrawCollider = false;


#endif // _DEBUG

};



