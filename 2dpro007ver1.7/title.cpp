#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
//#include "padinput.h"
#include "sound.h"

//マクロ定義
#define MAX_TEX (2)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	//頂点バッファへのポインタ
bool g_Select = false;
bool g_EndFrag = false;

//ポリゴンの初期化処理
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntTitle;

	//サウンドの生成
	PlaySound(SOUND_LABEL_BGM000);

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title00.png",//テクスチャのファイル名
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title01.png",//テクスチャのファイル名
		&g_pTextureTitle[1]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*MAX_TEX * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//右回りで設定
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 960.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 960.0f, 0.0f);

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
	g_pVtxBuffTitle->Unlock();
}
//ポリゴンの終了処理
void UninitTitle(void)
{
	int nCntTitle;

	for (nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	
	//テクスチャの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//ポリゴンの更新処理
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_Select = g_Select ^ 1;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_Z) == true || GetKeyboardTrigger(DIK_SPACE) == true)
	{//ENTERキーが押された

		if (g_Select == false)
		{
			//モード設定（ゲーム画面に移行）
			SetFade(MODE_GAME);
		}
		else if (g_Select == true)
		{
			g_EndFrag = true;
		}
	}
}
//ポリゴンの描画処理
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

								//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle[g_Select]);

	
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
	

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}
bool GetFrag(void)
{
	return g_EndFrag;
}