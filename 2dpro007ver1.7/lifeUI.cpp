#include "main.h"
#include "LifeUI.h"
#include "Player.h"

//マクロ定義
#define NUM_PLACE (5)	//スコアの最大桁数
#define TEX_SIZE (70)	//テクスチャの表示サイズ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureLifeUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeUI = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posLifeUI;	//スコアの位置
int g_nLifeUI;	//スコアの値

//ポリゴンの初期化処理
void InitLifeUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntLifeUI;

	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\lifestar.png",//テクスチャのファイル名
		&g_pTextureLifeUI);

	//スコアの初期化
	g_nLifeUI = 2;

	//位置の初期化
	g_posLifeUI = D3DXVECTOR3(980.0f, 240.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLifeUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffLifeUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntLifeUI = 0; nCntLifeUI < NUM_PLACE; nCntLifeUI++)
	{
		pVtx[0].pos.x = g_posLifeUI.x - 20;	//右回りで設定
		pVtx[0].pos.y = g_posLifeUI.y - 20;
		pVtx[0].pos.z = g_posLifeUI.z;
		pVtx[1].pos.x = g_posLifeUI.x + 20;
		pVtx[1].pos.y = g_posLifeUI.y - 20;
		pVtx[1].pos.z = g_posLifeUI.z;
		pVtx[2].pos.x = g_posLifeUI.x - 20;
		pVtx[2].pos.y = g_posLifeUI.y + 20;
		pVtx[2].pos.z = g_posLifeUI.z;
		pVtx[3].pos.x = g_posLifeUI.x + 20;
		pVtx[3].pos.y = g_posLifeUI.y + 20;
		pVtx[3].pos.z = g_posLifeUI.z;

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
	g_pVtxBuffLifeUI->Unlock();
}
//ポリゴンの終了処理
void UninitLifeUI(void)
{
	//テクスチャの破棄
	if (g_pTextureLifeUI != NULL)
	{
		g_pTextureLifeUI->Release();
		g_pTextureLifeUI = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffLifeUI != NULL)
	{
		g_pVtxBuffLifeUI->Release();
		g_pVtxBuffLifeUI = NULL;
	}
}
//ポリゴンの更新処理
void UpdateLifeUI(void)
{
	int nCntLifeUI, nNum1, nNum2;
	
	//テクスチャの更新
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffLifeUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);


	for (nCntLifeUI = 0; nCntLifeUI <NUM_PLACE ; nCntLifeUI++)
	{
		pVtx[0].pos.x = g_posLifeUI.x-20+nCntLifeUI*40;	//右回りで設定
		pVtx[0].pos.y = g_posLifeUI.y - 20;
		pVtx[0].pos.z = g_posLifeUI.z;
		pVtx[1].pos.x = g_posLifeUI.x+20+nCntLifeUI*40;
		pVtx[1].pos.y = g_posLifeUI.y - 20;
		pVtx[1].pos.z = g_posLifeUI.z;
		pVtx[2].pos.x = g_posLifeUI.x-20+nCntLifeUI*40;
		pVtx[2].pos.y = g_posLifeUI.y + 20;
		pVtx[2].pos.z = g_posLifeUI.z;
		pVtx[3].pos.x = g_posLifeUI.x+20+nCntLifeUI*40;
		pVtx[3].pos.y = g_posLifeUI.y + 20;
		pVtx[3].pos.z = g_posLifeUI.z;

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
	g_pVtxBuffLifeUI->Unlock();
}
//ポリゴンの描画処理
void DrawLifeUI(void)
{
	int nCntLifeUI;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	Player PlayerLife = GetPlayer();

								//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLifeUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLifeUI);

	for (nCntLifeUI = 0; nCntLifeUI <  PlayerLife.nLife - 1; nCntLifeUI++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLifeUI * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}