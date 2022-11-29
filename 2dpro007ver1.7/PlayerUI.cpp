#include "main.h"
#include "Player.h"
#include "PlayerUI.h"

//マクロ定義
#define MAX_DATA (3)
#define MAX_TEX (13)

//構造体の定義
typedef enum
{
	TYPE_LIFE = 0,
	TYPE_BOMB,
	TYPE_MANUVER
}Type;

typedef struct
{
	Type type;
	bool bUse;

}UIdata;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTexturePlayerUI[MAX_TEX] = {};	//テクスチャ3枚分へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerUI = NULL;	//頂点バッファへのポインタ
UIdata g_aUIdata[MAX_TEX] = {};
float g_aTexV2;	//テクスチャ座標の開始位置(V値)

//ポリゴンの初期化処理
void InitPlayerUI(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

								//デバイスの取得
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\lifestar.png",//テクスチャのファイル名
		&g_apTexturePlayerUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bombstar.png",//テクスチャのファイル名
		&g_apTexturePlayerUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//テクスチャのファイル名
		&g_apTexturePlayerUI[2]);

	//敵の初期化
	g_aUIdata[0].type = TYPE_LIFE;

	for (nCnt = 1; nCnt <3 ; nCnt++)
	{
		g_aUIdata[nCnt].type =TYPE_BOMB;
	}
	for (nCnt = 3; nCnt <6; nCnt++)
	{
		g_aUIdata[nCnt].type = TYPE_MANUVER;
	}

	for (nCnt = 0; nCnt < MAX_TEX;nCnt++)
	{
		g_aUIdata[nCnt].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayerUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
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

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPlayerUI->Unlock();
}
//ポリゴンの終了処理
void UninitPlayerUI(void)
{
	int nCnt;

	//テクスチャの破棄
	for (nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		if (g_apTexturePlayerUI[nCnt] != NULL)
		{
			g_apTexturePlayerUI[nCnt]->Release();
			g_apTexturePlayerUI[nCnt] = NULL;
		}
	}

	//バッファの破棄
	if (g_pVtxBuffPlayerUI != NULL)
	{
		g_pVtxBuffPlayerUI->Release();
		g_pVtxBuffPlayerUI = NULL;
	}
}
//ポリゴンの更新処理
void UpdatePlayerUI(void)
{
	int nCnt,nCnt2;
	Player PlayerData3 = GetPlayer();

	for (nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		g_aUIdata[nCnt].bUse == false;

	}

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		switch (g_aUIdata[nCnt].type)
		{
		case TYPE_LIFE:
			g_aUIdata[nCnt].bUse = PlayerData3.nLife - 1;
			break;

		case TYPE_BOMB:
			for (nCnt2 = 0; nCnt2 < PlayerData3.nBomb; nCnt2++)
			{
				g_aUIdata[nCnt].bUse = PlayerData3.nBomb;
				break;
			}
			break;

		case TYPE_MANUVER:
			for (nCnt2 = 0; nCnt2 < 3; nCnt2++)
			{
				g_aUIdata[nCnt].bUse = true;
				break;
			}
		
			break;
		}
		
	}

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayerUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCnt = 0; nCnt <MAX_TEX ; nCnt++)
	{
			switch (g_aUIdata[nCnt].type)
			{
			case TYPE_LIFE:
				for (nCnt2 = nCnt; nCnt2 < 1; nCnt2++)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(960.0f, 220.0f, 0.0f);	//右回りで設定
					pVtx[1].pos = D3DXVECTOR3(1000.0f, 220.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(960.0f, 260.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(1000.0f, 260.0f, 0.0f);

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

					pVtx += 4;
					
				}

				break;

			case TYPE_BOMB:
				for (nCnt2 = nCnt; nCnt2 <3; nCnt2++)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 260.0f, 0.0f);	//右回りで設定
					pVtx[1].pos = D3DXVECTOR3(940.0f + nCnt2 * 40, 260.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 300.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(940.0f + nCnt2 * 40, 300.0f, 0.0f);

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

					pVtx += 4;
					
				}

				break;

			case TYPE_MANUVER:
				for (nCnt2 = nCnt; nCnt2 < 6; nCnt2++)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 350.0f, 0.0f);	//右回りで設定
					pVtx[1].pos = D3DXVECTOR3(980.0f + nCnt2 * 40, 350.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 430.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(980.0f + nCnt2 * 40, 430.0f, 0.0f);

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
					pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(1.0f, 0.1f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f);

					pVtx += 4;
					
				}

				break;
			}
		
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffPlayerUI->Unlock();
}
//ポリゴンの描画処理
void DrawPlayerUI(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

								//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_aUIdata[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTexturePlayerUI[g_aUIdata[nCnt].type]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
		
	}
	
}