#include "main.h"
#include "Bullet.h"
#include "input.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Player.h"
#include "Score.h"
#include "effect.h"
#include "sound.h"

//マクロ定義
#define MAX_BULLET (1280)	//弾の最大数

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 rot;			//角度
	D3DXVECTOR3 rotmove;		//角度移動量
	D3DXCOLOR col;				//色
	int nLife;					//寿命
	BULLETTYPE type;			//弾の種類
	BALLISTICSTYPE ballistics;	//弾道の種類
	bool bManuver = false;		//マニューバフラグ
	bool bUse;					//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void CollisionEnemy(Bullet*pBullet);
void CollisionPlayer(Bullet*pBullet);
void CollisionPlayerManuver(Bullet*pBullet);


//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureBullet[BULLETTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];
Player g_PlayerData2;
int g_BattleCnt = 0;
int g_Toggle=1;
float g_fAngleBullet;
float g_fLengthBullet;

//ポリゴンの初期化処理
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntBullet;

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャの読み込み

	//自機弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet001.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_PLAYER]);

	//自機オプション
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\laser00.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_PLAYER_01]);

	//自機オプション
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\laser00.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_PLAYER_02]);

	//自機ボム
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bomb00.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_PLAYER_BOMB]);

	//小弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet002.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_00]);

	//大弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet003.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_01]);

	//札弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet004.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_02]);

	//大吉弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet005.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_03]);

	//吉弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet006.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_04]);

	//小吉弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet007.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_05]);

	//末吉弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet008.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_06]);

	//凶弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet009.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_07]);

	//大凶弾
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet010.png",//テクスチャのファイル名
		&g_apTextureBullet[BULLETTYPE_ENEMY_08]);


	//対角線の長さを算出
	g_fLengthBullet = sqrtf(66.0f*66.0f + 66.0f*66.0f)*0.5f;
	//対角線の角度を算出する
	g_fAngleBullet = atan2f(66.0f, 66.0f);

	//弾の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 30;
		g_aBullet[nCntBullet].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].ballistics = BALLISTICSTYPE_NORMAL;
		g_aBullet[nCntBullet].bManuver = false;
		g_aBullet[nCntBullet].bUse = false;
	}
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//右回りで設定
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//テクスチャの場合全て白に
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}
//ポリゴンの終了処理
void UninitBullet(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < BULLETTYPE_MAX; nCntBullet++)
	{
		//テクスチャの破棄
		if (g_apTextureBullet[nCntBullet] != NULL)
		{
			g_apTextureBullet[nCntBullet]->Release();
			g_apTextureBullet[nCntBullet] = NULL;
		}
	}

	//テクスチャの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//ポリゴンの更新処理
void UpdateBullet(void)
{
	int nCntBullet,nScore;

	g_BattleCnt++;

	g_PlayerData2 = GetPlayer();
	

		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffBullet->Lock(
			0,
			0,
			(void**)&pVtx,
			0
		);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている

		//=============================================================================
		//弾のサイズ
		//=============================================================================
			if (g_aBullet[nCntBullet].type >= BULLETTYPE_ENEMY_03)
			{
				//対角線の長さを算出
				g_fLengthBullet = sqrtf(240.0f*240.0f + 240.0f*240.0f)*0.5f;
				//対角線の角度を算出する
				g_fAngleBullet = atan2f(240.0f, 240.0f);
			}

			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY_02)
			{
				//対角線の長さを算出
				g_fLengthBullet = sqrtf(56.0f*56.0f + 56.0f*56.0f)*0.5f;
				//対角線の角度を算出する
				g_fAngleBullet = atan2f(56.0f, 56.0f);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_BOMB)
			{
				//対角線の長さを算出
				g_fLengthBullet = sqrtf(1000.0f*1000.0f + 920.0f*920.0f)*0.5f;
				//対角線の角度を算出する
				g_fAngleBullet = atan2f(920.0f, 1000.0f);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_01|| g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_02)
			{
				//対角線の長さを算出
				g_fLengthBullet = sqrtf(1000.0f*1000.0f + 45.0f*45.0f)*0.5f;
				//対角線の角度を算出する
				g_fAngleBullet = atan2f(45.0f, 1000.0f);
			}
			else
			{
				//対角線の長さを算出
				g_fLengthBullet = sqrtf(66.0f*66.0f + 66.0f*66.0f)*0.5f;
				//対角線の角度を算出する
				g_fAngleBullet = atan2f(66.0f, 66.0f);
			}
			
		//=============================================================================
		//落下弾の設定
		//=============================================================================	
			if (g_aBullet[nCntBullet].ballistics == BALLISTICSTYPE_FALL)
			{
				
				g_aBullet[nCntBullet].move += D3DXVECTOR3(0.0f, 0.1f, 0.0f);

				if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY_00)
				{
					if (g_BattleCnt == 299)
					{
						if (rand() % 2 == 0)
						{
							g_Toggle = -1;
						}
						else
						{
							g_Toggle = 1;
						}
					}

					if (g_BattleCnt >= 300 && g_BattleCnt<600)
					{

						g_aBullet[nCntBullet].move += D3DXVECTOR3((float)5 * g_Toggle / 100, 0.0f, 0.0f);
						g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.5*g_Toggle);
					}
					if (g_BattleCnt >= 600)
					{
						g_BattleCnt = 0;
					}
				}
				

			}

			//=============================================================================
			//反射弾の設定
			//=============================================================================	
			if (g_aBullet[nCntBullet].ballistics == BALLISTICSTYPE_REFLECT)
			{

					if (g_aBullet[nCntBullet].pos.x<=GAMEAREA_MIN|| g_aBullet[nCntBullet].pos.x>=GAMEAREA_WIDTH_MAX|| g_aBullet[nCntBullet].pos.y<=GAMEAREA_MIN)
					{
						g_aBullet[nCntBullet].move.x = g_aBullet[nCntBullet].move.x*-1;
						g_aBullet[nCntBullet].move.y = g_aBullet[nCntBullet].move.y*-1;

						g_aBullet[nCntBullet].ballistics = BALLISTICSTYPE_NORMAL;
					}
					

			}
		//=============================================================================
		//ポリゴンの設定
		//=============================================================================
			 //位置を更新
			

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_BOMB)
			{
				g_aBullet[nCntBullet].pos = D3DXVECTOR3(g_PlayerData2.pos.x, g_PlayerData2.pos.y-550.0f, 0.0f);
			}
			else if(g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_01)
			{
				
					g_aBullet[nCntBullet].pos = D3DXVECTOR3(g_PlayerData2.pos.x + 45, g_PlayerData2.pos.y-500, 0.0f);
				
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_02)
			{

				g_aBullet[nCntBullet].pos = D3DXVECTOR3(g_PlayerData2.pos.x -45, g_PlayerData2.pos.y - 500, 0.0f);

			}
			else
			{
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			}

			////角度を更新
			//g_aBullet[nCntBullet].rot += g_aBullet[nCntBullet].rotmove;

			//頂点座標の設定
			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot.z + (-D3DX_PI + g_fAngleBullet)) * g_fLengthBullet;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot.z + (-D3DX_PI + g_fAngleBullet)) * g_fLengthBullet;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot.z + (D3DX_PI - g_fAngleBullet)) * g_fLengthBullet;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot.z + (D3DX_PI - g_fAngleBullet)) * g_fLengthBullet;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot.z + -g_fAngleBullet) * g_fLengthBullet;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot.z + -g_fAngleBullet) * g_fLengthBullet;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot.z + g_fAngleBullet) * g_fLengthBullet;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot.z + g_fAngleBullet) * g_fLengthBullet;
			pVtx[3].pos.z = 0.0f;

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aBullet[nCntBullet].col;
			pVtx[1].col = g_aBullet[nCntBullet].col;	//テクスチャの場合全て白に
			pVtx[2].col = g_aBullet[nCntBullet].col;
			pVtx[3].col = g_aBullet[nCntBullet].col;

			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			////エフェクトの設定
			//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 33.0f, 10);



			//=============================================================================
			//ヒット判定処理
			//=============================================================================
			if (g_aBullet[nCntBullet].type >= BULLETTYPE_PLAYER&& g_aBullet[nCntBullet].type <= BULLETTYPE_PLAYER_BOMB)
			{
				CollisionEnemy(&g_aBullet[nCntBullet]);
			}
			if (g_aBullet[nCntBullet].type >= BULLETTYPE_ENEMY_00)
			{
				CollisionPlayer(&g_aBullet[nCntBullet]);
			}
			if (g_aBullet[nCntBullet].type >= BULLETTYPE_ENEMY_00)
			{
				CollisionPlayerManuver(&g_aBullet[nCntBullet]);
			}

			//=============================================================================
			//弾消し処理
			//=============================================================================
			if (g_PlayerData2.state == PLAYERSTATE_BOMB&&g_aBullet[nCntBullet].type>=BULLETTYPE_ENEMY_00)
			{
				if (g_aBullet[nCntBullet].pos.y <= g_PlayerData2.pos.y)
				{
					g_aBullet[nCntBullet].bUse = false;
					nScore=200;
					AddScore(&nScore);
				}
				
			}
			bool BulletDlt =GetBulletDlt();
			if (BulletDlt == true)
			{
				if (g_aBullet[nCntBullet].type >= BULLETTYPE_ENEMY_00)
				{
					g_aBullet[nCntBullet].bUse = false;
					nScore = 400;
					AddScore(&nScore);
				}
				
			}

			if (g_PlayerData2.state == PLAYERSTATE_NOEFFECT&&g_aBullet[nCntBullet].type >= BULLETTYPE_ENEMY_00)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_BOMB)
			{
				if (g_PlayerData2.state != PLAYERSTATE_BOMB)
				{
					g_aBullet[nCntBullet].bUse = false;
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_01|| g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER_02)
			{
				if (GetKeyboardPress(DIK_Z) ==false)
				{
					StopSound(SOUND_LABEL_SE_SHOT);
					g_aBullet[nCntBullet].bUse = false;
			
				}
			}
			else
			{
				if (g_aBullet[nCntBullet].pos.y <= GAMEAREA_MIN - 100 || g_aBullet[nCntBullet].pos.y >= (float)GAMEAREA_HEIGHT_MAX + 100 || g_aBullet[nCntBullet].pos.x <= GAMEAREA_MIN - 100 || g_aBullet[nCntBullet].pos.x >= (float)GAMEAREA_WIDTH_MAX + 100)
				{
					g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
				}
			}
			
			if (g_aBullet[nCntBullet].type >= BULLETTYPE_ENEMY_03)
			{
				if (g_aBullet[nCntBullet].pos.y >= 460.0f)
				{
					
					float fAnglePlayer = atan2f(420.0f - g_PlayerData2.pos.x,460.0f - g_PlayerData2.pos.y);
					switch (g_aBullet[nCntBullet].type)
					{
					case BULLETTYPE_ENEMY_03:
						//大吉
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 2.5f, 0, 2, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						break;


					case BULLETTYPE_ENEMY_04:
						//吉
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 2.5f, 16, 0, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 5.0f, 16, 0, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 7.5f, 16, 0, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));

						break;


					case BULLETTYPE_ENEMY_05:
						//小吉

						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), 0.0f, 2.5f, 16, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), 0.0f, 5.0f, 16, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), 0.0f, 7.5f, 16, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						break;

					case BULLETTYPE_ENEMY_06:
						//末吉
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 2.5f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 5.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 7.5f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						
						break;

					case BULLETTYPE_ENEMY_07:
						//凶
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), 3.14f, 2.5f, 33, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), 3.14f, 5.0f, 33, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), 3.14f, 7.5f, 33, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						break;


					case BULLETTYPE_ENEMY_08:
						//大凶
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 1.0f, 33, 1,D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 2.0f, 33, 1,D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 3.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 4.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 5.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 6.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 7.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 8.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 9.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
						SetBarrage(D3DXVECTOR3(420.0f, 460.0f, 0.0f), fAnglePlayer, 10.0f, 33, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));

						break;

					}
					g_aBullet[nCntBullet].bUse = false;
					g_aBullet[nCntBullet].bManuver = false;
				}
			}
			//g_aBullet[nCntBullet].nLife--;	//寿命のカウントダウン
			//if (g_aBullet[nCntBullet].nLife <= 0)
			//{
			//	SetExplosion(g_aBullet[nCntBullet].pos);//爆発をセット
			//	g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
			//}
			
		}
pVtx += 4;
	}
		//頂点バッファをアンロックする
		g_pVtxBuffBullet->Unlock();
}
//ポリゴンの描画処理
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntBullet;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
		 //テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBullet[g_aBullet[nCntBullet].type]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBullet*4, 2);
		}
	}
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}
//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fTexAngle, BULLETTYPE type,BALLISTICSTYPE ballistics, D3DXCOLOR col)
{
	int nCntBullet;

	//頂点座標の設定
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].pos = pos;

			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x + -33;	//右回りで設定
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y + -33 ;
			pVtx[0].pos.z = g_aBullet[nCntBullet].pos.z + 0.0f;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + 33;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y + -33;
			pVtx[1].pos.z = g_aBullet[nCntBullet].pos.z + 0.0f;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x + -33;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + 33;
			pVtx[2].pos.z = g_aBullet[nCntBullet].pos.z + 0.0f;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + 33;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + 33;
			pVtx[3].pos.z = g_aBullet[nCntBullet].pos.z + 0.0f;

			break;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	g_aBullet[nCntBullet].ballistics = ballistics;
	g_aBullet[nCntBullet].move = move;
	g_aBullet[nCntBullet].rot.z = fTexAngle;
	g_aBullet[nCntBullet].col = col;
	g_aBullet[nCntBullet].nLife = 30;
	g_aBullet[nCntBullet].bUse = true;	//使用している状態にする
}
//敵当たり判定処理
void CollisionEnemy(Bullet*pBullet)
{
Enemy *pEnemy = GetEnemy();
int nCntEnemy;

for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
{
	if (pEnemy->bUse == true)
	{//敵が使用されている
		if (pBullet->type == BULLETTYPE_PLAYER)
		{
			if (pBullet->pos.x >= pEnemy->pos.x - 50 && pBullet->pos.x <= pEnemy->pos.x + 50 && pBullet->pos.y >= pEnemy->pos.y && pBullet->pos.y <= pEnemy->pos.y + 100)
			{//敵のヒット処理

				HitEnemy(nCntEnemy, 2);
				pBullet->bUse = false;
			}
		}
		else if (pBullet->type == BULLETTYPE_PLAYER_01 || pBullet->type == BULLETTYPE_PLAYER_02)
		{
			if (pBullet->pos.x+45 >= pEnemy->pos.x - 50 && pBullet->pos.x-45 <= pEnemy->pos.x + 50 && pBullet->pos.y+500 >= pEnemy->pos.y)
			{//敵のヒット処理

				HitEnemy(nCntEnemy, 1);
			}
		}
		else if(pBullet->type == BULLETTYPE_PLAYER_BOMB)
		{
			if (pBullet->pos.x-460 <= pEnemy->pos.x - 50 && pBullet->pos.x+460 >= pEnemy->pos.x + 50 && pBullet->pos.y-500 <= pEnemy->pos.y && pBullet->pos.y+500 >= pEnemy->pos.y + 100)
			{//敵のヒット処理

				HitEnemy(nCntEnemy, 2);
			}
		}
		
	}
}
}
//プレイヤー当たり判定処理
void CollisionPlayer(Bullet*pBullet)
{
	
	int nCntPlayer;

	if (pBullet->pos.x >= g_PlayerData2.pos.x-5 && pBullet->pos.x <= g_PlayerData2.pos.x + 5 && pBullet->pos.y >= g_PlayerData2.pos.y-5 && pBullet->pos.y <= g_PlayerData2.pos.y + 5)
	{
		if (g_PlayerData2.state == PLAYERSTATE_NORMAL)
		{
			HitPlayer(1);
		}
		pBullet->bUse = false;
	}
}
//プレイヤーマニューバ判定処理
void CollisionPlayerManuver(Bullet*pBullet)
{
	int nCntPlayer;
	int nScore;

	if (pBullet->bManuver == false)
	{
		if (pBullet->pos.x >= g_PlayerData2.pos.x - 50 && pBullet->pos.x <= g_PlayerData2.pos.x + 50 && pBullet->pos.y >= g_PlayerData2.pos.y - 50 && pBullet->pos.y <= g_PlayerData2.pos.y + 50)
		{
			nScore = 400;
			ManuverPlayer();
			AddScore(&nScore);

			pBullet->bManuver = true;
		}
	}
	
}
//弾幕攻撃処理
void SetBarrage(D3DXVECTOR3 BossPos,float fAngle, float fmove, int nWay,int nBarrageType, D3DXCOLOR col)
{
	int nCnt,nCnt2,nWay1,nWay2,nWay3;


	switch (nBarrageType)
	{
	case 0://自機狙い全方位奇数n-way弾
		nWay1 = nWay;
			for (nCnt = 0; nCnt <nWay1; nCnt++)
			{

				SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + (((fAngle * 100 + 314) + (628 / nWay1*nCnt))-314) / 100) * fmove, cosf(-D3DX_PI + (((fAngle * 100 + 314) + (628 / nWay1 * nCnt)) - 314) / 100) * fmove, 0.0f), (((fAngle * 100 + 314) + (628 / nWay1 * nCnt)) - 314) / 100, BULLETTYPE_ENEMY_02,BALLISTICSTYPE_NORMAL,col);
			}
			PlaySound(SOUND_LABEL_SE_SHOT02);
		break;

		
	case 1://固定偶数n-way弾
		nWay2 = nWay;
		for (nCnt2 = 0; nCnt2 <nWay2; nCnt2++)
		{
			SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + (((fAngle * 100 + 314) + (628 / nWay2 * nCnt2)) - 314) / 100) * fmove, cosf(-D3DX_PI + (((fAngle * 100 + 314) + (628 / nWay2 * nCnt2)) - 314) / 100) * fmove, 0.0f), (((fAngle * 100 + 314) + (628 / nWay2 * nCnt2)) - 314) / 100, BULLETTYPE_ENEMY_02,BALLISTICSTYPE_NORMAL,col);
		}
		PlaySound(SOUND_LABEL_SE_SHOT01);
		break;


	case 2://自機狙い5連弾
		SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + fAngle) * fmove, cosf(-D3DX_PI + fAngle) * fmove, 0.0f), fAngle ,BULLETTYPE_ENEMY_02,BALLISTICSTYPE_NORMAL,col);
		SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + fAngle) *( fmove+2.5f), cosf(-D3DX_PI + fAngle) * (fmove+2.5f), 0.0f),fAngle, BULLETTYPE_ENEMY_02,BALLISTICSTYPE_NORMAL,col);
		SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + fAngle) * (fmove+5.0f), cosf(-D3DX_PI + fAngle) *( fmove+5.0f), 0.0f),fAngle, BULLETTYPE_ENEMY_02,BALLISTICSTYPE_NORMAL,col);
		SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + fAngle) * (fmove+7.5f), cosf(-D3DX_PI + fAngle) * (fmove+7.5f), 0.0f), fAngle,BULLETTYPE_ENEMY_02,BALLISTICSTYPE_NORMAL,col);
		SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + fAngle) * (fmove+10.0f), cosf(-D3DX_PI + fAngle) * (fmove+10.0f), 0.0f),fAngle, BULLETTYPE_ENEMY_02,BALLISTICSTYPE_NORMAL,col);
		PlaySound(SOUND_LABEL_SE_SHOT01);
		break;


	case 3://ランダム落下弾
		for (nCnt = 0; nCnt < nWay; nCnt++)
		{
			
			SetBullet(D3DXVECTOR3((float)(rand() % 800 + 20), (float)(rand() % 300 + 20), 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), fAngle, BULLETTYPE_ENEMY_00,BALLISTICSTYPE_FALL,col);
		}
		break;

	case 4 ://ランダムnWay弾
		for (nCnt = 0; nCnt < nWay; nCnt++)
		{

			SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + (rand()%628-314)/100) * fmove, cosf(-D3DX_PI + (rand()%628-314)/100) * fmove, 0.0f), (((fAngle * 100 + 314) + (628 / nWay * nCnt)) - 314) / 100, BULLETTYPE_ENEMY_02, BALLISTICSTYPE_NORMAL,col);
		}
		break;

	case 5:
		nWay3 = nWay;
		for (nCnt2 = 0; nCnt2 <nWay3; nCnt2++)
		{
			SetBullet(BossPos, D3DXVECTOR3(sinf(-D3DX_PI + (((fAngle * 100 + 314) + (628 / nWay3 * nCnt2)) - 314) / 100) * fmove, cosf(-D3DX_PI + (((fAngle * 100 + 314) + (628 / nWay3 * nCnt2)) - 314) / 100) * fmove, 0.0f), (((fAngle * 100 + 314) + (628 / nWay3 * nCnt2)) - 314) / 100, BULLETTYPE_ENEMY_02, BALLISTICSTYPE_REFLECT, col);
		}
		PlaySound(SOUND_LABEL_SE_SHOT01);
		break;
	}
}
