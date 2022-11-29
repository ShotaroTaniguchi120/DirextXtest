#include "main.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Score.h"
#include "sound.h"
#include "input.h"

//マクロ定義
#define NUM_ENEMY (6)	//敵の種類

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;	//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];
VERTEX_2D g_aVertex[NUM_ENEMY];
int g_aBulletRate[MAX_ENEMY];
int g_BossTimeCnt = 0;
int g_BossState = 0;
int g_BossToggle = 1;
bool g_bShotEnemyFrag = true;
bool g_BulletDlt = false;
float g_fAngleFixed = 3.14f;

//ポリゴンの初期化処理
void InitEnemy(void)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ago.png",//テクスチャのファイル名
		&g_apTextureEnemy[0]);
	
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\food_curryruce.png",//テクスチャのファイル名
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\kontyuusaisyuu.png",//テクスチャのファイル名
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\DarkMater.png",//テクスチャのファイル名
		&g_apTextureEnemy[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\boss001.png",//テクスチャのファイル名
		&g_apTextureEnemy[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\EnemyOption00.png",//テクスチャのファイル名
		&g_apTextureEnemy[5]);

	
	//敵の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].bUse = false;
		g_aBulletRate[nCntEnemy] = 0;
		g_aEnemy[nCntEnemy].nCounterAnimEnemy = 0;	//カウンターを初期化する
		g_aEnemy[nCntEnemy].nPatternAnimEnemy = 0;	//パターンNo.を初期化する

		g_aEnemy[nCntEnemy].nLifeGage = 0;			//体力ゲージ数の初期化
	}
	g_BossTimeCnt = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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

		pVtx+=4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//ポリゴンの終了処理
void UninitEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		//テクスチャの破棄
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//テクスチャの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//ポリゴンの更新処理
void UpdateEnemy(void)
{
	int nCntEnemy;

	if (GetKeyboardTrigger(DIK_N) == true)
	{
		g_bShotEnemyFrag = g_bShotEnemyFrag ^ 1;
	}

	////アニメーションの設定
	//g_aEnemy[nCntEnemy].nCounterAnimEnemy++;	//カウンターを加算
	//if ((g_aEnemy[nCntEnemy].nCounterAnimEnemy % 2) == 0)
	//{
	//	g_aEnemy[nCntEnemy].nPatternAnimEnemy = (g_aEnemy[nCntEnemy].nPatternAnimEnemy + 1) % 8;		//パターンNo.を更新する
	//}
		//テクスチャの更新

		VERTEX_2D*pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(
			0,
			0,
			(void**)&pVtx,
			0
		);

		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
		{

			if (g_aEnemy[nCntEnemy].bUse == true)
			{//敵が使用されている

			 //位置の更新
				g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

				switch (g_aEnemy[nCntEnemy].ntype)
				{
				case 4:
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - 65;	//右回りで設定
					pVtx[0].pos.y = 120.0f - 65;
					pVtx[0].pos.z = g_aEnemy[nCntEnemy].pos.z;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + 65;
					pVtx[1].pos.y = 120.0f - 65;
					pVtx[1].pos.z = g_aEnemy[nCntEnemy].pos.z;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - 65;
					pVtx[2].pos.y = 120.0f + 65;
					pVtx[2].pos.z = g_aEnemy[nCntEnemy].pos.z;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + 65;
					pVtx[3].pos.y = 120.0f + 65;
					pVtx[3].pos.z = g_aEnemy[nCntEnemy].pos.z;
					break;



				default:
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - 50;	//右回りで設定
					pVtx[0].pos.y = 120.0f - 50;
					pVtx[0].pos.z = g_aEnemy[nCntEnemy].pos.z;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + 50;
					pVtx[1].pos.y = 120.0f - 50;
					pVtx[1].pos.z = g_aEnemy[nCntEnemy].pos.z;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - 50;
					pVtx[2].pos.y = 120.0f + 50;
					pVtx[2].pos.z = g_aEnemy[nCntEnemy].pos.z;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + 50;
					pVtx[3].pos.y = 120.0f + 50;
					pVtx[3].pos.z = g_aEnemy[nCntEnemy].pos.z;
					break;


				}
				//rhwの設定
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				switch (g_aEnemy[nCntEnemy].state)
				{
				default :
					g_BulletDlt = false;
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//テクスチャの場合全て白に
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					break;

				case ENEMYSTATE_DAMEGE:
					g_BulletDlt = false;
					g_aEnemy[nCntEnemy].nCounterState--;
					if (g_aEnemy[nCntEnemy].nCounterState <= 0)
					{
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					}
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);	
					pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);

					break;

				case ENEMYSTATE_NOEFFECT:
					g_aEnemy[nCntEnemy].nCounterState--;
					if (g_aEnemy[nCntEnemy].nCounterState <= 0)
					{
						g_BossTimeCnt = 0;
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					}
					
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

					break;
				}
				

				//テクスチャの座標の設定
				//pVtx[0].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnimEnemy * 0.125f, 0.0f);
				//pVtx[1].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnimEnemy * 0.125f+0.125f, 0.0f);
				//pVtx[2].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnimEnemy * 0.125f, 1.0f);
				//pVtx[3].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnimEnemy * 0.125f+0.125f, 1.0f);
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				//ザコ敵の攻撃
				if (g_aEnemy[nCntEnemy].ntype != 4)
				{
					if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_NOEFFECT)
					{
						g_aBulletRate[nCntEnemy]++;
						if (g_aBulletRate[nCntEnemy] % 10 == 0)
						{
							/*SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), 0.0f,BULLETTYPE_ENEMY_00, BALLISTICSTYPE_NORMAL);*/

							if (g_bShotEnemyFrag == true)
							{

								//プレイヤーとの角度を算出する
								Player g_Player = GetPlayer();
								float fAnglePlayer = atan2f(g_aEnemy[nCntEnemy].pos.x - g_Player.pos.x, 120.0f - g_Player.pos.y);

								SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(-D3DX_PI + fAnglePlayer) * 10, cosf(-D3DX_PI + fAnglePlayer) * 10, 0.0f), fAnglePlayer,BULLETTYPE_ENEMY_00, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
							}
						}
					}
				}

				//ボスの攻撃
				if (g_aEnemy[nCntEnemy].ntype == 4)
				{
					if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_NOEFFECT)
					{
						Player g_PlayerData = GetPlayer();
						float fAnglePlayer = atan2f(g_aEnemy[nCntEnemy].pos.x - g_PlayerData.pos.x, 120.0f - g_PlayerData.pos.y);

						g_BossTimeCnt++;

				
						switch (g_aEnemy[nCntEnemy].nLifeGage)
						{
						case 5:
							switch (g_BossTimeCnt)
							{
							case 10:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 5.0f, 33,0, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								break;
							case 20:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 5.0f, 33,0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								break;

							case 50:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 5.0f,33, 0, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								break;
							case 60:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 5.0f, 33,0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								break;

							case 90:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 2.5f,0, 2,D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								break;
							case 95:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 2.5f, 0,2, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));

							case 125:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 2.5f, 0,2, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								break;
							case 130:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 2.5f,0, 2, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								break;

							case 160:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 5.0f,33, 0,D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								break;
							case 170:
								SetBarrage(g_aEnemy[nCntEnemy].pos, fAnglePlayer, 5.0f,33, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								break;

							}

							if (g_BossTimeCnt >= 220)
							{
								g_BossTimeCnt = 0;
							}


							break;



						case 4:
							if (g_BossTimeCnt % 15== 0)
							{
								SetBarrage({}, NULL, 10.0f, 5,3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
							}

							break;


						case 3:
							if (g_BossTimeCnt % 2 == 0)
							{
								SetBarrage(g_aEnemy[nCntEnemy].pos, g_fAngleFixed, 5.0f, 1, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								g_fAngleFixed -= 0.157;
							}
							if (g_BossTimeCnt % 2 == 0)
							{
								SetBarrage(g_aEnemy[nCntEnemy].pos, g_fAngleFixed+3.14f, 5.0f, 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								
							}

							if (g_fAngleFixed <-3.14)
							{
							g_fAngleFixed = g_fAngleFixed*-1;
							}
							

							if (g_BossTimeCnt == 60)
							{
								g_BossToggle = rand() % 3;
								if (g_BossToggle==1&&g_aEnemy[nCntEnemy].pos.x>160)
								{
									g_BossToggle = -1;
								}
								else if(g_BossToggle==2&&g_aEnemy[nCntEnemy].pos.x<640)
								{
									g_BossToggle = 1;
								}
								else
								{
									g_BossToggle = 0;
								}
								g_aEnemy[nCntEnemy].move += D3DXVECTOR3(5.0f * g_BossToggle, 0.0f, 0.0f);

								
							}

							if (g_BossTimeCnt == 90)
							{
								g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

								g_BossTimeCnt = 0;
							}
							
							
							break;

						case 2:
							
							if (g_BossTimeCnt % 2 == 0)
							{
								SetBarrage(g_aEnemy[nCntEnemy].pos, g_fAngleFixed, 5.0f, 1, 1, D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
								g_fAngleFixed -= 0.157;
							}
							if (g_BossTimeCnt % 2 == 0)
							{
								SetBarrage(g_aEnemy[nCntEnemy].pos, g_fAngleFixed + 3.14f, 5.0f, 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

							}

							if (g_fAngleFixed <-3.14)
							{
								g_fAngleFixed = g_fAngleFixed*-1;
							}


							if (g_BossTimeCnt == 60)
							{
								g_BossToggle = rand() % 3;
								if (g_BossToggle == 1 && g_aEnemy[nCntEnemy].pos.x>160)
								{
									g_BossToggle = -1;
								}
								else if (g_BossToggle == 2 && g_aEnemy[nCntEnemy].pos.x<640)
								{
									g_BossToggle = 1;
								}
								else
								{
									g_BossToggle = 0;
								}
								g_aEnemy[nCntEnemy].move += D3DXVECTOR3(5.0f * g_BossToggle, 0.0f, 0.0f);


							}

							if (g_BossTimeCnt == 90)
							{
								g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							}

							
							if (g_BossTimeCnt% 180==0)
							{

								g_BossToggle = rand() % 100;

								if (g_BossToggle >= 0 && g_BossToggle < 5)
								{//大吉
									SetBullet(D3DXVECTOR3(400.0f, -60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0.0f, BULLETTYPE_ENEMY_03, BALLISTICSTYPE_FALL,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

								}


								else if (g_BossToggle >= 5 && g_BossToggle < 25)
								{//吉
									SetBullet(D3DXVECTOR3(400.0f, -60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0.0f, BULLETTYPE_ENEMY_04, BALLISTICSTYPE_FALL,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

								}


								else if (g_BossToggle >= 25 && g_BossToggle < 65)
								{//小吉
									SetBullet(D3DXVECTOR3(400.0f, -60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0.0f, BULLETTYPE_ENEMY_05, BALLISTICSTYPE_FALL,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

								}
								else if (g_BossToggle >= 65 && g_BossToggle < 80)
								{//末吉
									SetBullet(D3DXVECTOR3(400.0f, -60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0.0f, BULLETTYPE_ENEMY_06, BALLISTICSTYPE_FALL,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				
								}
								else if (g_BossToggle >= 80 && g_BossToggle < 95)
								{//凶
									SetBullet(D3DXVECTOR3(400.0f, -60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0.0f, BULLETTYPE_ENEMY_07, BALLISTICSTYPE_FALL,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								}
								else if (g_BossToggle >= 95 && g_BossToggle < 100)
								{//大凶
									SetBullet(D3DXVECTOR3(400.0f, -60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0.0f, BULLETTYPE_ENEMY_08, BALLISTICSTYPE_FALL,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								}

								g_BossTimeCnt = 0;
							}

							break;

					
						case 1:
							if (g_BossTimeCnt ==180)
							{
								SetBarrage(g_aEnemy[nCntEnemy].pos, 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
							}
							
							if (g_BossTimeCnt == 360)
							{
								SetBarrage(D3DXVECTOR3(420.0f-380, 120.0f, 0.0f), 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
								SetBarrage(D3DXVECTOR3(420.0f + 380, 120.0f, 0.0f), 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
							}

							
							if (g_BossTimeCnt > 720)
							{
								if (g_aEnemy[nCntEnemy].nLife >= 1000)
								{
									if (g_BossTimeCnt % 180 == 0)
									{
										g_BossToggle = rand() % 300 + 1 - 150;
										SetBarrage(D3DXVECTOR3(420.0f +g_BossToggle, 120.0f+ g_BossToggle, 0.0f), 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
									}
								}
								if (g_aEnemy[nCntEnemy].nLife < 1000 && g_aEnemy[nCntEnemy].nLife>500)
								{
									if (g_BossTimeCnt % 150==0)
									{
										g_BossToggle = rand() % 300 + 1 - 150;
										SetBarrage(D3DXVECTOR3(420.0f + g_BossToggle, 120.0f + g_BossToggle, 0.0f), 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
									}
									if (g_BossTimeCnt % 150 == 0)
									{
										g_BossToggle = rand() % 300 + 1 - 150;
										SetBarrage(D3DXVECTOR3(420.0f + g_BossToggle, 120.0f + g_BossToggle, 0.0f), 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
									}
								}
								if (g_aEnemy[nCntEnemy].nLife <= 500)
								{
									if (g_BossTimeCnt % 120==0)
									{
										g_BossToggle = rand() % 300 + 1 - 150;
										SetBarrage(D3DXVECTOR3(420.0f + g_BossToggle, 120.0f + g_BossToggle, 0.0f), 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
									}
									if (g_BossTimeCnt % 120 == 0)
									{
										g_BossToggle = rand() % 300 + 1 - 150;
										SetBarrage(D3DXVECTOR3(420.0f + g_BossToggle, 120.0f + g_BossToggle, 0.0f), 0.0f, 5.0f, 88, 5, D3DXCOLOR(0.2f, 0.2f, 0.8f, 1.0f));
									}
								}
								
							}
						}
						

					}
				}
				
			}
			pVtx += 4;
		}
		
		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
}
//ポリゴンの描画処理
void DrawEnemy(void)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

		

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].ntype]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}
//敵の設定処理
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	//頂点座標の設定
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//弾が使用されていない
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].ntype = nType;
			g_aEnemy[nCntEnemy].nLife = g_aEnemy[nCntEnemy].ntype * 4 + 1;

			if (g_aEnemy[nCntEnemy].ntype == 4)
			{
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOEFFECT;
				g_aEnemy[nCntEnemy].nCounterState = 60;

				//ボスのライフ設定
				g_aEnemy[nCntEnemy].nLife = 1500;
				g_aEnemy[nCntEnemy].nLifeGage = 5;
			}

			g_aEnemy[nCntEnemy].bUse = true;	//使用している状態にする

			break;
		}
	}
}
//敵のヒット処理
void HitEnemy(int nCntEnemy, int nDamage)
{
	int nPoint;

	if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_NOEFFECT)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;
		nPoint = nDamage;
		AddScore(&nPoint);
		if (g_aEnemy[nCntEnemy].nLife <= 0)
		{
			g_BulletDlt = true;
			if (g_aEnemy[nCntEnemy].nLifeGage > 1)
			{
				PlaySound(SOUND_LABEL_SE_BREAK00);
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOEFFECT;
				g_aEnemy[nCntEnemy].nCounterState = 120;
				g_aEnemy[nCntEnemy].nLife = 1500;
				
				if (g_aEnemy[nCntEnemy].nLifeGage == 2)
				{
					g_aEnemy[nCntEnemy].nLife = 2500;
				}
				
				g_aEnemy[nCntEnemy].nLifeGage--;
				

				//if (g_aEnemy[nCntEnemy].nLifeGage == 6)
				//{
				//	SetEnemy(D3DXVECTOR3(220.0f, 200.0f, 0.0f), 5);
				//	SetEnemy(D3DXVECTOR3(620.0f, 200.0f, 0.0f), 5);
				//}
			}
			else
			{
				SetExplosion(g_aEnemy[nCntEnemy].pos);
				switch (g_aEnemy[nCntEnemy].ntype)
				{
				case 0:
					nPoint = 10;
					break;
				case 1:
					nPoint = 100;
					break;
				case 2:
					nPoint = 1000;
					break;
				case 3:
					nPoint = 10000;
					break;
				}
				AddScore(&nPoint);
				g_aEnemy[nCntEnemy].bUse = false;
			}

		}
		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;
			g_aEnemy[nCntEnemy].nCounterState = 5;	//ダメージ状態を保つ時間

													//頂点座標の設定
			VERTEX_2D*pVtx;	//頂点情報へのポインタ

							//頂点バッファをロックし頂点情報へのポインタを取得
			g_pVtxBuffEnemy->Lock(
				0,
				0,
				(void**)&pVtx,
				0
			);

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);	//テクスチャの場合全て白に
			pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);

			//頂点バッファをアンロックする
			g_pVtxBuffEnemy->Unlock();
		}
	}
	
}
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
bool GetBulletDlt(void)
{
	return g_BulletDlt;
}