#ifndef _Enemy_H_	//このマクロが定義されていなければ
#define _Enemy_H_	//二重インクルード防止マクロ

//マクロ定義
#define MAX_ENEMY (128)	//敵の最大数

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL=0,	//通常
	ENEMYSTATE_DAMEGE,		//ダメージエフェクト
	ENEMYSTATE_NOEFFECT,	//無敵状態
	ENEMYSTATE_OPTION,		//オプション
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nCounterAnimEnemy;	//アニメーションカウンター
	int nPatternAnimEnemy;	//アニメーションパターンナンバー
	int ntype;			//種類
	int nLife;			//体力
	int nLifeGage;		//体力ゲージ数
	ENEMYSTATE state;	//状態
	int nCounterState;	//ステートカウンター
	bool bUse;			//使用しているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int Damage);
Enemy *GetEnemy(void);
bool GetBulletDlt(void);

#endif // !_Enemy_H_
