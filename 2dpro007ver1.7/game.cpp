#include "main.h"
#include "game.h"
#include "input.h"
#include "Player.h"
#include "Bg.h"
#include "gameUI.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "fade.h"
#include "effect.h"
#include "Score.h"
#include "LifeUI.h"
#include "sound.h"
#include "lifeUI.h"
#include "bombUI.h"
#include "manuverUI.h"

//マクロ定義
#define NUM_PLACE (8)	//スコアの最大桁数
#define TEX_SIZE (70)	//テクスチャの表示サイズ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureGame = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posGame;							//スコアの位置
int g_EndDelay = 0;								//終了前遅延カウント
bool g_bPoseFrag = false;						//ポーズフラグ
bool g_BossFrag = false;						//ボス戦フラグ

//ポリゴンの初期化処理
void InitGame(void)
{
	g_BossFrag = false;

	//背景の初期化処理
	InitBg();

	//プレイヤーの初期化処理
	InitPlayer();

	//弾の初期化処理
	InitBullet();
	
	//エフェクトの初期化処理
	InitEffect();

	//爆発の初期化処理
	InitExplosion();

	//エネミーの初期化処理
	InitEnemy();

	//ゲームUIの初期化処理
	InitGameUI();

	//プレイヤーUIの初期化処理
	InitLifeUI();
	InitBombUI();
	InitManuverUI();

	PlaySound(SOUND_LABEL_BGM001);
	SetEnemy(D3DXVECTOR3(420.0f, 120.0f, 0.0f), 4);

	g_BossFrag = true;
	g_EndDelay = 0;

	//スコアの初期化処理
	InitScore();

	srand(time(NULL));

}
//ポリゴンの終了処理
void UninitGame(void)
{
	//ゲームUIの終了処理
	UninitGameUI();
	//プレイヤー終了処理
	UninitLifeUI();
	UninitBombUI();
	UninitManuverUI();
	//背景の終了処理
	UninitBg();
	//プレイヤーの終了処理
	UninitPlayer();
	//エフェクトの終了処理
	UninitEffect();
	//弾の終了処理
	UninitBullet();
	//エネミーの終了処理
	UninitEnemy();
	//爆発の終了処理
	UninitExplosion();
	////スコアの終了処理
	//UninitScore();
}
//ポリゴンの更新処理
void UpdateGame(void)
{
	int nCntEnemy, nEnemyNumCnt;

	//ポーズチェック
	if (g_bPoseFrag == false)
	{

		//背景の更新処理
		UpdateBg();

		//プレイヤーの更新処理
		UpdatePlayer();

		//エフェクトの更新処理
		UpdateEffect();

		//弾の更新処理
		UpdateBullet();

		//エネミーの更新処理
		UpdateEnemy();

		//爆発の更新処理
		UpdateExplosion();

		//ゲームUIの更新処理
		UpdateGameUI();

		//プレイヤーUIの更新処理
		UpdateLifeUI();
		UpdateBombUI();
		UpdateManuverUI();

		//スコアの更新処理
		UpdateScore();

		Player PlayerData3 = GetPlayer();
		Enemy *pEnemy = GetEnemy();

		nEnemyNumCnt = 0;

		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
		{
			if (pEnemy->bUse == true)
			{
				nEnemyNumCnt++;
			}
		}

		if (nEnemyNumCnt == 0&&g_BossFrag==false)
		{
			
		}

		if (g_BossFrag == true)
		{
			if (nEnemyNumCnt==0)
			{
				g_EndDelay++;

				if (g_EndDelay == 180)
				{
					SetFade(MODE_RESULT);
				}
				
			}
		}

		if (PlayerData3.bUse == false)
		{
			g_EndDelay++;

			if (g_EndDelay == 30)
			{
				SetFade(MODE_RESULT);
			}
			
		}
	}

	if (GetKeyboardTrigger(DIK_P) == true)
	{//Pキーが押された
		g_bPoseFrag = g_bPoseFrag ^ 1;
	}
}

//ポリゴンの描画処理
void DrawGame(void)
{

	//背景の描画処理
	DrawBg();

	//プレイヤーの描画処理
	DrawPlayer();

	//エフェクトの描画処理
	DrawEffect();

	//弾の描画処理
	DrawBullet();

	//エネミーの描画処理
	DrawEnemy();

	//爆発の描画処理
	DrawExplosion();

	//ゲームUIの描画処理
	DrawGameUI();

	//プレイヤーUIの描画処理
	DrawLifeUI();
	DrawBombUI();
	DrawManuverUI();

	//スコアの描画処理
	DrawScore();
}