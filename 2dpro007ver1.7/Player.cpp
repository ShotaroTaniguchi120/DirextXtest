#include "main.h"
#include "Player.h"
#include "input.h"
#include "Bullet.h"
#include "Explosion.h"
#include "sound.h"

//マクロ定義
#define MAX_TEXTURE (4)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
Player g_Player;
float g_fLengthPlayer;	//対角線の長さ
float g_fMoveLengthPlayer;	//対角線の長さの移動
float g_fAnglePlayer;	//対角線の角度
int g_BulletRate = 0;

//ポリゴンの初期化処理
void InitPlayer(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Player000.png",//テクスチャのファイル名
		&g_apTexturePlayer[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\jikihantei.png",//テクスチャのファイル名
		&g_apTexturePlayer[3]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\option00.png",//テクスチャのファイル名
		&g_apTexturePlayer[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\option00.png",//テクスチャのファイル名
		&g_apTexturePlayer[1]);


	g_Player.nCounterAnimPlayer = 0;	//カウンターを初期化する
	g_Player.nPatternAnimPlayer = 0;	//パターンNo.を初期化する

	g_Player.pos = D3DXVECTOR3(420.0f, 900.0f, 0.0f);	//位置を初期化
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量を初期化
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
	g_Player.nLife = 2;
	g_Player.nBomb = 2;
	g_Player.nManuver = 0;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.bSlowMode = false;
	g_Player.bUse = true;
	//対角線の長さを算出
	g_fLengthPlayer = sqrtf(120.0f*120.0f + 120.0f*120.0f)*0.5f;
	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(120.0f, 120.0f);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//テクスチャの場合全て白に
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//ポリゴンの終了処理
void UninitPlayer(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTexturePlayer[nCnt] != NULL)
		{
			g_apTexturePlayer[nCnt]->Release();
			g_apTexturePlayer[nCnt] = NULL;
		}
	}

	//テクスチャの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//ポリゴンの更新処理
void UpdatePlayer(void)
{
	int nCnt;

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Player.bSlowMode = true;
	}
	else if (GetKeyboardPress(DIK_LSHIFT) == false)
	{
		g_Player.bSlowMode = false;
	}

	if (GetKeyboardPress(DIK_Z) == true&&g_Player.state!=PLAYERSTATE_BOMB)
	{//Zキーが押された
		g_BulletRate++;
		if ((g_BulletRate % 5) == 0)
		{
			//弾の設定
			SetBullet(g_Player.pos + D3DXVECTOR3(16.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -20.0f, 0.0f),0.0f, BULLETTYPE_PLAYER,BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_Player.pos - D3DXVECTOR3(16.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -20.0f, 0.0f),0.0f, BULLETTYPE_PLAYER, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}

	if (GetKeyboardTrigger(DIK_Z) == true && g_Player.state != PLAYERSTATE_BOMB)
	{//Zキーが押された
		PlaySound(SOUND_LABEL_SE_SHOT);
		SetBullet(g_Player.pos + D3DXVECTOR3(45.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, BULLETTYPE_PLAYER_01, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetBullet(g_Player.pos - D3DXVECTOR3(45.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, BULLETTYPE_PLAYER_02, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}


	if (GetKeyboardTrigger(DIK_X) == true)
	{//Xキーが押された

		if (g_Player.state != PLAYERSTATE_BOMB&&g_Player.nBomb > 0)
		{
			//ボム発動状態にする
			PlaySound(SOUND_LABEL_SE_BOMB);
			g_Player.state = PLAYERSTATE_BOMB;
			g_Player.nCounterState = 240;
			g_Player.nBomb -- ;
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - 550 , 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, BULLETTYPE_PLAYER_BOMB, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		
	}

	if (GetKeyboardPress(DIK_LEFT) == true && g_Player.pos.x >= GAMEAREA_MIN)
	{//←キーが押された

		if (GetKeyboardPress(DIK_UP) == true && g_Player.pos.y >= GAMEAREA_MIN)
		{
			g_Player.pos.x += sinf(-D3DX_PI*-0.75f)*-10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI *-0.75f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true && g_Player.pos.y <= GAMEAREA_HEIGHT_MAX)
		{
			g_Player.pos.x += sinf(-D3DX_PI *-0.105f)*-10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI *-0.105f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else
		{
			//位置を更新
			g_Player.pos.x += -10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);

		}

	}
	else if (GetKeyboardPress(DIK_RIGHT) == true && g_Player.pos.x <= GAMEAREA_WIDTH_MAX)
	{//→キーが押された

		if (GetKeyboardPress(DIK_UP) == true && g_Player.pos.y >= GAMEAREA_MIN)
		{
			g_Player.pos.x += sinf(-D3DX_PI *0.75f)*-10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI *0.75f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true && g_Player.pos.y <= GAMEAREA_HEIGHT_MAX)
		{
			g_Player.pos.x += sinf(-D3DX_PI *-0.105f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI * -0.105f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else
		{
			//位置を更新
			g_Player.pos.x += 10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}

	}
	else if (GetKeyboardPress(DIK_UP) == true && g_Player.pos.y >= GAMEAREA_MIN)
	{//↑キーが押された

		if (GetKeyboardPress(DIK_RIGHT) == false && GetKeyboardPress(DIK_LEFT) == false)
		{
			//位置を更新
			g_Player.pos.y += -10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true && g_Player.pos.y <= GAMEAREA_HEIGHT_MAX)
	{//↓キーが押された

		if (GetKeyboardPress(DIK_RIGHT) == false && GetKeyboardPress(DIK_LEFT) == false)
		{
			//位置を更新
			g_Player.pos.y += 10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
	}
	//if (GetKeyboardPress(DIK_R) == true)
	//{//上キーが入力されたとき
	// //拡大
	//	if (g_fLengthPlayer < 110.0f)
	//	{//サイズが限界を超えていなければ
	//		g_fMoveLengthPlayer += 0.5f;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_F) == true)
	//{//下キーが入力されたとき
	// //縮小
	//	if (g_fLengthPlayer >50.0f)
	//	{//サイズが最小限界を超えていなければ
	//		g_fMoveLengthPlayer -= 0.5f;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{//左キーが入力されたとき
	// //左回転
	//	g_Player.moverot.z += (D3DX_PI * 0.002f);
	//	if (g_Player.moverot.z > D3DX_PI || g_Player.moverot.z < -D3DX_PI)
	//	{//角度がΠを超えたとき
	//		g_Player.moverot.z *= -1;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_E) == true)
	//{//右キーが入力されたとき
	//	g_Player.moverot.z += (-D3DX_PI * 0.002f);
	//	if (g_Player.moverot.z > D3DX_PI || g_Player.moverot.z < -D3DX_PI)
	//	{//角度がΠを超えたとき
	//		g_Player.moverot.z *= -1;
	////	}
	//}

	/*g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;*/
	g_Player.rot.z += g_Player.moverot.z;	//回転
	g_fLengthPlayer += g_fMoveLengthPlayer;	//拡大縮小
	//移動量を更新（減衰）
	/*g_Player.move.x += (0.0f - g_Player.move.x)*0.1;
	g_Player.move.y += (0.0f - g_Player.move.y)*0.1;*/
	g_Player.moverot.z += (0.0f - g_Player.moverot.z) * 0.05;	//回転速度
	g_fMoveLengthPlayer += (0.0f - g_fMoveLengthPlayer) * 0.1;	//拡大縮小

	for (nCnt = 0; nCnt < 1 + g_Player.bSlowMode+g_Player.bOption*2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			//=========================================================================================================
			//頂点座標の設定
			pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			switch (g_Player.state)
			{
			case PLAYERSTATE_BOMB:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;

			case PLAYERSTATE_DAMEGE:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NOEFFECT;
					g_Player.nCounterState = 240;
				}
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);

				break;

			case PLAYERSTATE_NOEFFECT:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

				break;


			default:
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//テクスチャの場合全て白に
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			}

			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;

		case 3:
			//=========================================================================================================
			//頂点座標の設定
			pVtx[0].pos.x = g_Player.pos.x - 5;
			pVtx[0].pos.y = g_Player.pos.y - 5;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + 5;
			pVtx[1].pos.y = g_Player.pos.y - 5;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x - 5;
			pVtx[2].pos.y = g_Player.pos.y + 5;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + 5;
			pVtx[3].pos.y = g_Player.pos.y + 5;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			switch (g_Player.state)
			{
			

			case PLAYERSTATE_BOMB:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;

			case PLAYERSTATE_DAMEGE:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NOEFFECT;
					g_Player.nCounterState = 240;
				}
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);

				break;

			case PLAYERSTATE_NOEFFECT:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

				break;

			default:
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//テクスチャの場合全て白に
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			}

			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;

		case 1:
			//=========================================================================================================
			//頂点座標の設定
			pVtx[0].pos.x = g_Player.pos.x - 15-45;
			pVtx[0].pos.y = g_Player.pos.y - 15;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + 15-45;
			pVtx[1].pos.y = g_Player.pos.y - 15;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x - 15-45;
			pVtx[2].pos.y = g_Player.pos.y + 15;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + 15-45;
			pVtx[3].pos.y = g_Player.pos.y + 15;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;


				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//テクスチャの場合全て白に
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			

			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;


		case 2:
			//=========================================================================================================
			//頂点座標の設定
			pVtx[0].pos.x = g_Player.pos.x - 15 + 45;
			pVtx[0].pos.y = g_Player.pos.y - 15;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + 15 + 45;
			pVtx[1].pos.y = g_Player.pos.y - 15;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x - 15 + 45;
			pVtx[2].pos.y = g_Player.pos.y + 15;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + 15 + 45;
			pVtx[3].pos.y = g_Player.pos.y + 15;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;


			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//テクスチャの場合全て白に
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//ポリゴンの描画処理
void DrawPlayer(void)
{
	int nCntPlayer;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

								//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPlayer = 0; nCntPlayer <1 + g_Player.bSlowMode+g_Player.bOption*2; nCntPlayer++)
	{
		if (g_Player.bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTexturePlayer[nCntPlayer]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayer * 4, 2);
		}
	}
}
//自機のヒット処理
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;


	PlaySound(SOUND_LABEL_SE_HITPLAYER);

	if (g_Player.nLife <= 0)
	{
		SetExplosion(g_Player.pos);
		g_Player.bUse = false;
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMEGE;
		g_Player.nCounterState = 10;	//ダメージ状態を保つ時間

									//頂点座標の設定
		VERTEX_2D*pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(
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
		g_pVtxBuffPlayer->Unlock();
	}
}
//自機のヒット処理
void ManuverPlayer(void)
{
	g_Player.nManuver++;


	PlaySound(SOUND_LABEL_SE_CANCEL);

}
Player GetPlayer(void)
{
	return g_Player;
}