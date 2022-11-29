#include "main.h"
#include "ManuverUI.h"
#include "Player.h"

//マクロ定義
#define NUM_PLACE (3)	//スコアの最大桁数
#define TEX_SIZE (70)	//テクスチャの表示サイズ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureManuver = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffManuver = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posManuver;	//スコアの位置
int g_nManuver;	//スコアの値

				//ポリゴンの初期化処理
void InitManuverUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntManuver;

	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//テクスチャのファイル名
		&g_pTextureManuver);

	//スコアの初期化
	g_nManuver = 0;

	//位置の初期化
	g_posManuver = D3DXVECTOR3(1005.0f, 423.0f, 0.0);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffManuver,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffManuver->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		pVtx[0].pos.x = g_posManuver.x - 35;	//右回りで設定
		pVtx[0].pos.y = g_posManuver.y - 35;
		pVtx[0].pos.z = g_posManuver.z;
		pVtx[1].pos.x = g_posManuver.x + 35;
		pVtx[1].pos.y = g_posManuver.y - 35;
		pVtx[1].pos.z = g_posManuver.z;
		pVtx[2].pos.x = g_posManuver.x - 35;
		pVtx[2].pos.y = g_posManuver.y + 35;
		pVtx[2].pos.z = g_posManuver.z;
		pVtx[3].pos.x = g_posManuver.x + 35;
		pVtx[3].pos.y = g_posManuver.y + 35;
		pVtx[3].pos.z = g_posManuver.z;

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
		pVtx[1].tex = D3DXVECTOR2(0.0f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f + 0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
		g_posManuver.x += 35;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffManuver->Unlock();
}
//ポリゴンの終了処理
void UninitManuverUI(void)
{
	//テクスチャの破棄
	if (g_pTextureManuver != NULL)
	{
		g_pTextureManuver->Release();
		g_pTextureManuver = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffManuver != NULL)
	{
		g_pVtxBuffManuver->Release();
		g_pVtxBuffManuver = NULL;
	}
}
//ポリゴンの更新処理
void UpdateManuverUI(void)
{
	int nCntManuver, nNum1, nNum2;
	int aTexU[NUM_PLACE] = {};	//各桁の数字を格納

	Player PlayerData4 = GetPlayer();
	g_nManuver = PlayerData4.nManuver;

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		nNum1 = pow(10, nCntManuver + 1);
		nNum2 = pow(10, nCntManuver);
		aTexU[nCntManuver] = (g_nManuver % nNum1) / nNum2;
	}

	//テクスチャの更新
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffManuver->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	pVtx += 8;

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aTexU[nCntManuver] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aTexU[nCntManuver] * 0.1f) + 0.1f, 1.0f);

		pVtx -= 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffManuver->Unlock();
}
//ポリゴンの描画処理
void DrawManuverUI(void)
{
	int nCntManuver;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

								//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffManuver, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureManuver);

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntManuver * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}
////スコアの設定処理
//void SetManuver(int nManuver)
//{
//	int aTexU[NUM_PLACE];	//各桁の数字を格納
//	int nCntManuver;
//
//	g_nManuver = nManuver;
//	for (nCntManuver = NUM_PLACE; nCntManuver <= 0; nCntManuver--)
//	{
//		aTexU[nCntManuver] = g_nManuver % (10 ^ (nCntManuver + 1)) / (10 ^ nCntManuver);
//	}
//
//	//頂点座標の設定
//	VERTEX_2D*pVtx;	//頂点情報へのポインタ
//
//					//頂点バッファをロックし頂点情報へのポインタを取得
//	g_pVtxBuffManuver->Lock(
//		0,
//		0,
//		(void**)&pVtx,
//		0
//	);
//
//	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
//	{
//		//テクスチャの座標の設定
//		pVtx[0].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f + 0.1f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f + 0.1f, 1.0f);
//
//		pVtx += 4;
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffManuver->Unlock();
//
//}
//void AddManuver(int *pValue)
//{
//	g_nManuver += *pValue;
//}