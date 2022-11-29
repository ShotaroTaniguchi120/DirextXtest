#include "main.h"
#include "Explosion.h"
#include "input.h"

//マクロ定義
#define MAX_Explosion (128)	//爆発の最大数

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DCOLOR col;	//色
	int nCounterAnimExplosion;	//アニメーションカウンター
	int nPatternAnimExplosion;	//アニメーションパターンナンバー
	bool bUse;			//使用しているかどうか
}Explosion;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_Explosion];

//ポリゴンの初期化処理
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntExplosion;

	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",//テクスチャのファイル名
		&g_pTextureExplosion);

	//爆発の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(255, 255, 255,100);
		g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
		g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Explosion,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
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
		pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//ポリゴンの終了処理
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//ポリゴンの更新処理
void UpdateExplosion(void)
{
	int nCntExplosion;
	//テクスチャの更新
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている

		 //頂点座標の設定
			pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x + -33;	//右回りで設定
			pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + -33;
			pVtx[0].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;
			pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + 33;
			pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + -33;
			pVtx[1].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;
			pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x + -33;
			pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + 33;
			pVtx[2].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;
			pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + 33;
			pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + 33;
			pVtx[3].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;

			g_aExplosion[nCntExplosion].nCounterAnimExplosion++;
			if ((g_aExplosion[nCntExplosion].nCounterAnimExplosion % 8) == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnimExplosion = (g_aExplosion[nCntExplosion].nPatternAnimExplosion + 1);		//パターンNo.を更新する
			}

			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].nPatternAnimExplosion >= 8)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//ポリゴンの描画処理
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntExplosion;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている
		 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}
//爆発の設定処理
void SetExplosion(D3DXVECTOR3 pos)
{
	int nCntExplosion;

	//頂点座標の設定
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//爆発が使用されていない
			g_aExplosion[nCntExplosion].pos = pos;

			g_aExplosion[nCntExplosion].col = D3DXCOLOR(255, 255, 255, 100);
			g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
			g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;
			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 1.0f);

			break;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();

	g_aExplosion[nCntExplosion].bUse = true;	//使用している状態にする
}