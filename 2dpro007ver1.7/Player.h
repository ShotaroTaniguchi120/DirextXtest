#ifndef _Player_H_	//このマクロが定義されていなければ
#define _Player_H_	//二重インクルード防止マクロ

//自機の状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//通常
	PLAYERSTATE_DAMEGE,		//ダメージエフェクト
	PLAYERSTATE_NOEFFECT,	//無敵状態
	PLAYERSTATE_BOMB,		//ボム状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//自機構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//位置
	D3DXVECTOR3 rot;	//位置
	D3DXVECTOR3 moverot;	//位置
	int nCounterAnimPlayer;	//アニメーションカウンター
	int nPatternAnimPlayer;	//アニメーションパターンナンバー
	int nLife;			//体力
	int nBomb;			//ボム数
	int nManuver;		//マニューバ数
	PLAYERSTATE state;	//状態
	int nCounterState;	//ステートカウンター
	bool bSlowMode;		//低速モード
	bool bOption = true;		//オプション
	bool bUse;			//使用しているかどうか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
void ManuverPlayer(void);
Player GetPlayer(void);

#endif // !_Player_H_
