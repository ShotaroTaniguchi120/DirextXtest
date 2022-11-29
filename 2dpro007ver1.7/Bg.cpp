
#include "main.h"
#include "Bg.h"

//マクロ定義
#define NUM_BG (3)		//背景の数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureBg =NULL;	//テクスチャ3枚分へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//頂点バッファへのポインタ
float g_aTexV[NUM_BG];	//テクスチャ座標の開始位置(V値)

//ポリゴンの初期化処理
void InitBg(void)
{
	int nCntBg;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	
	//デバイスの取得
	pDevice = GetDevice();
								
	//テクスチャの読み込み
	//for (nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	//{
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\bg.png",//テクスチャのファイル名
	//		&g_apTextureBg);
	//}

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg02.png",//テクスチャのファイル名
			&g_apTextureBg);
	

	

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(
		0,
		0,
		(void**)&pVtx,
		0
		);
	
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(20.0f, 20.0f, 0.0f);	//右回りで設定
		pVtx[1].pos = D3DXVECTOR3(820.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(20.0f, 940.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(820.0f, 940.0f, 0.0f);

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

		

	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}
//ポリゴンの終了処理
void UninitBg(void)
{
	int nCntBg;

	//テクスチャの破棄
	
	if (g_apTextureBg != NULL)
	{
		g_apTextureBg->Release();
		g_apTextureBg = NULL;
	}
	
	//バッファの破棄
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}
//ポリゴンの更新処理
void UpdateBg(void)
{


}
//ポリゴンの描画処理
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntBg;

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBg);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}