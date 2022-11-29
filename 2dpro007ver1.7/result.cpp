#include "main.h"
#include "result.h"
#include "fade.h"
#include "input.h"
#include "ranking.h"
#include "rankingname.h"
#include "Score.h"

//マクロ定義
#define MAX_TEX (2)


//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ
int g_Deley = 0;


//ポリゴンの初期化処理
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntResult;

	g_Deley = 0;
	

	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\resultbg.png",//テクスチャのファイル名
		&g_pTextureResult[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ResultLogo.png",//テクスチャのファイル名
		&g_pTextureResult[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntResult = 0; nCntResult < MAX_TEX; nCntResult++)
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

		pVtx += 4;
	}
	

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	InitRanking();
	UpdateRanking();

	SetScore(D3DXVECTOR3(720.0f, 600.0f, 0.0f));
	UpdateScore();

	InitRankingname();
}
//ポリゴンの終了処理
void UninitResult(void)
{
	int nCnt;

	UninitRanking();
	//スコアの終了処理
	UninitScore();

	

	//テクスチャの破棄

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureResult != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}
	
	//テクスチャの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	

	
}
//ポリゴンの更新処理
void UpdateResult(void)
{
	UpdateRankingname();
	bool bEndfrag = GetInputfrag();

	if (bEndfrag == true)
	{
		/*g_Deley++;
		if (g_Deley >= 120)
		{*/
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardTrigger(DIK_Z) == true)
			{//ENTERキーが押された
			 //モード設定（ゲーム画面に移行）
				SetFade(MODE_TITLE);
			}
		/*}*/
	}
	
	
}
//ポリゴンの描画処理
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCnt;
								//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt*4, 2);
	}
	


	DrawRanking();
	DrawScore();
	DrawRankingname();
}