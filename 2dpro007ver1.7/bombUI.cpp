#include "main.h"
#include "BombUI.h"
#include "Player.h"

//マクロ定義
#define NUM_PLACE (5)	//スコアの最大桁数
#define TEX_SIZE (70)	//テクスチャの表示サイズ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBombUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBombUI = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posBombUI;	//スコアの位置
int g_nBombUI;	//スコアの値

				//ポリゴンの初期化処理
void InitBombUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntBombUI;

	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bombstar.png",//テクスチャのファイル名
		&g_pTextureBombUI);

	//スコアの初期化
	g_nBombUI = 2;

	//位置の初期化
	g_posBombUI = D3DXVECTOR3(980.0f, 315.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBombUI,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBombUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntBombUI = 0; nCntBombUI < NUM_PLACE; nCntBombUI++)
	{
		pVtx[0].pos.x = g_posBombUI.x - 20;	//右回りで設定
		pVtx[0].pos.y = g_posBombUI.y - 20;
		pVtx[0].pos.z = g_posBombUI.z;
		pVtx[1].pos.x = g_posBombUI.x + 20;
		pVtx[1].pos.y = g_posBombUI.y - 20;
		pVtx[1].pos.z = g_posBombUI.z;
		pVtx[2].pos.x = g_posBombUI.x - 20;
		pVtx[2].pos.y = g_posBombUI.y + 20;
		pVtx[2].pos.z = g_posBombUI.z;
		pVtx[3].pos.x = g_posBombUI.x + 20;
		pVtx[3].pos.y = g_posBombUI.y + 20;
		pVtx[3].pos.z = g_posBombUI.z;

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
	g_pVtxBuffBombUI->Unlock();
}
//ポリゴンの終了処理
void UninitBombUI(void)
{
	//テクスチャの破棄
	if (g_pTextureBombUI != NULL)
	{
		g_pTextureBombUI->Release();
		g_pTextureBombUI = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffBombUI != NULL)
	{
		g_pVtxBuffBombUI->Release();
		g_pVtxBuffBombUI = NULL;
	}
}
//ポリゴンの更新処理
void UpdateBombUI(void)
{
	int nCntBombUI, nNum1, nNum2;

	//テクスチャの更新
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBombUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);


	for (nCntBombUI = 0; nCntBombUI <NUM_PLACE; nCntBombUI++)
	{
		pVtx[0].pos.x = g_posBombUI.x - 20 + nCntBombUI * 40;	//右回りで設定
		pVtx[0].pos.y = g_posBombUI.y - 20;
		pVtx[0].pos.z = g_posBombUI.z;
		pVtx[1].pos.x = g_posBombUI.x + 20 + nCntBombUI * 40;
		pVtx[1].pos.y = g_posBombUI.y - 20;
		pVtx[1].pos.z = g_posBombUI.z;
		pVtx[2].pos.x = g_posBombUI.x - 20 + nCntBombUI * 40;
		pVtx[2].pos.y = g_posBombUI.y + 20;
		pVtx[2].pos.z = g_posBombUI.z;
		pVtx[3].pos.x = g_posBombUI.x + 20 + nCntBombUI * 40;
		pVtx[3].pos.y = g_posBombUI.y + 20;
		pVtx[3].pos.z = g_posBombUI.z;

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
	g_pVtxBuffBombUI->Unlock();
}
//ポリゴンの描画処理
void DrawBombUI(void)
{
	int nCntBombUI;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	Player PlayerLife = GetPlayer();

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBombUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBombUI);

	for (nCntBombUI = 0; nCntBombUI < PlayerLife.nBomb; nCntBombUI++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBombUI * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}