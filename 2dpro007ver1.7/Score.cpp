#include "main.h"
#include "Score.h"
#include "Enemy.h"

//マクロ定義
#define NUM_PLACE (8)	//スコアの最大桁数
#define TEX_SIZE (70)	//テクスチャの表示サイズ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posScore;	//スコアの位置
int g_nScore;	//スコアの値
int g_nHighScore;

//ポリゴンの初期化処理
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntScore, nCntScore2;

	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//テクスチャのファイル名
		&g_pTextureScore);

	//スコアの初期化
	g_nScore = 0;


	//ランキングデータ読み込み処理
	FILE*pFile;//ファイルポインタを宣言

			   //ファイルを開く
	pFile = fopen("ranking.txt", "r");

	//成功分岐
	if (pFile != NULL)
	{
		
		//ファイルに入力された構造体の各要素を出力する

		/*fwrite(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/

		fscanf(pFile, "%d", &g_nHighScore);

		
	}
	else if(pFile ==NULL)
	{
		g_nHighScore = 0;
	}
	
	if (pFile != NULL)
	{
		//ファイルを閉じる
		fclose(pFile);
	}
	

	//位置の初期化
	g_posScore = D3DXVECTOR3(980.0f, 160.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE*2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore2 = 0; nCntScore2 < 2; nCntScore2++)
	{
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			pVtx[0].pos.x = g_posScore.x - 40;	//右回りで設定
			pVtx[0].pos.y = g_posScore.y - 40;
			pVtx[0].pos.z = g_posScore.z;
			pVtx[1].pos.x = g_posScore.x + 40;
			pVtx[1].pos.y = g_posScore.y - 40;
			pVtx[1].pos.z = g_posScore.z;
			pVtx[2].pos.x = g_posScore.x - 40;
			pVtx[2].pos.y = g_posScore.y + 40;
			pVtx[2].pos.z = g_posScore.z;
			pVtx[3].pos.x = g_posScore.x + 40;
			pVtx[3].pos.y = g_posScore.y + 40;
			pVtx[3].pos.z = g_posScore.z;

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
			g_posScore.x += 40;
		}
		g_posScore.x -= 320;
		g_posScore.y = 90;
	}
	

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//ポリゴンの終了処理
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//ポリゴンの更新処理
void UpdateScore(void)
{
	int nCntScore, nCntScore2, nNum1, nNum2;
	int aTexU[NUM_PLACE*2] = {};	//各桁の数字を格納

	if (g_nScore >= g_nHighScore)
	{
		g_nHighScore = g_nScore;
	}

		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			nNum1 = pow(10, nCntScore + 1);
			nNum2 = pow(10, nCntScore);
			aTexU[nCntScore] = (g_nScore % nNum1) / nNum2;
		}
	
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			nNum1 = pow(10, nCntScore + 1);
			nNum2 = pow(10, nCntScore);
			aTexU[nCntScore+8] = (g_nHighScore % nNum1) / nNum2;
		}

	//テクスチャの更新
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore2 = 0; nCntScore2 < 2; nCntScore2++)
	{

		for (nCntScore = 7; nCntScore >= 0; nCntScore--)
		{
			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(aTexU[nCntScore+nCntScore2*8] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((aTexU[nCntScore+nCntScore2*8] * 0.1f) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(aTexU[nCntScore+nCntScore2*8] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((aTexU[nCntScore+nCntScore2*8] * 0.1f) + 0.1f, 1.0f);

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//ポリゴンの描画処理
void DrawScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < 16; nCntScore++)
	{
		 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}
//スコアの設定処理
void SetScore(D3DXVECTOR3 pos)
{
	int aTexU[NUM_PLACE];	//各桁の数字を格納
	int nCntScore;

	g_posScore = pos;

	//頂点座標の設定
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		pVtx[0].pos.x = g_posScore.x - 40;	//右回りで設定
		pVtx[0].pos.y = g_posScore.y - 40;
		pVtx[0].pos.z = g_posScore.z;
		pVtx[1].pos.x = g_posScore.x + 40;
		pVtx[1].pos.y = g_posScore.y - 40;
		pVtx[1].pos.z = g_posScore.z;
		pVtx[2].pos.x = g_posScore.x - 40;
		pVtx[2].pos.y = g_posScore.y + 40;
		pVtx[2].pos.z = g_posScore.z;
		pVtx[3].pos.x = g_posScore.x + 40;
		pVtx[3].pos.y = g_posScore.y + 40;
		pVtx[3].pos.z = g_posScore.z;


		g_posScore.x += 40;
		pVtx += 4;
	}

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	//テクスチャの場合全て白に
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		pVtx += 4;
	}


	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

}
void AddScore(int *pValue)
{
	g_nScore += *pValue;
}
//スコアの取得
int GetScore(void)
{
	return g_nScore;
}