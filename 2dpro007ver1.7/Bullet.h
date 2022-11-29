#ifndef _Bullet_h_	//このマクロが定義されていなければ
#define _Bullet_h_	//二重インクルード防止マクロ

#include "main.h"

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER=0,	//プレイヤーの弾
	BULLETTYPE_PLAYER_01,
	BULLETTYPE_PLAYER_02,
	BULLETTYPE_PLAYER_BOMB,
	BULLETTYPE_ENEMY_00,		//敵の弾
	BULLETTYPE_ENEMY_01,
	BULLETTYPE_ENEMY_02,
	BULLETTYPE_ENEMY_03,
	BULLETTYPE_ENEMY_04,
	BULLETTYPE_ENEMY_05,
	BULLETTYPE_ENEMY_06,
	BULLETTYPE_ENEMY_07,
	BULLETTYPE_ENEMY_08,
	BULLETTYPE_MAX
}BULLETTYPE;

//弾道の種類
typedef enum
{
	BALLISTICSTYPE_NORMAL=0,	//通常
	BALLISTICSTYPE_FALL,		//落下
	BALLISTICSTYPE_REFLECT,		//反射
	BALLISTICSTYPE_MAX
}BALLISTICSTYPE;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fTexAngle, BULLETTYPE type,BALLISTICSTYPE ballistics, D3DXCOLOR col);
void SetBarrage(D3DXVECTOR3 BossPos, float fAngle, float fmove, int nWay, int nBarrageType, D3DXCOLOR col);
#endif // !_Bullet_h_
