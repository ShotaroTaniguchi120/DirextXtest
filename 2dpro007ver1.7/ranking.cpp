#include "main.h"
#include "Ranking.h"
#include "rankingname.h"
#include "Score.h"

//マクロ定義
#define NUM_PLACE (8)	//スコアの最大桁数
#define TEX_SIZE (70)	//テクスチャの表示サイズ
#define NUM_RANKING (10)
#define MAX_NAME (10)



//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posRanking;	//スコアの位置
D3DXVECTOR3 g_posName;	//名前の位置
Ranking g_aRanking[NUM_RANKING] = {};
bool g_bPlayerSet = false;

//ポリゴンの初期化処理
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntRanking, nCntRanking2;

	g_bPlayerSet = false;

	for (nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		g_aRanking[nCntRanking].bPlayer = false;
	}
	//==============================================================
	//データの読み込み処理
	//==============================================================

	FILE*pFile;//ファイルポインタを宣言

			   //ファイルを開く
	pFile = fopen("ranking.txt", "r");

	//失敗分岐
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen("ranking.txt", "w");
		//ファイルに入力された構造体の各要素を出力する

		/*fwrite(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/
		for (nCntRanking = 0; nCntRanking <NUM_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", g_aRanking[nCntRanking].nScore);
			for (nCntRanking2 = 0; nCntRanking2 < 10; nCntRanking2++)
			{
				fprintf(pFile, "%d\n", 78);
			}
			
		}
		

		//ファイルを閉じる
		fclose(pFile);

		//ファイルを再度開く
		pFile = fopen("ranking.txt", "r");

	}

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //ファイルに入力された構造体の要素を出力する

		/*fread(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/
		for (nCntRanking = 0; nCntRanking <NUM_RANKING; nCntRanking++)
		{
			fscanf(pFile, "%d", &g_aRanking[nCntRanking].nScore);
			for (nCntRanking2 = 0; nCntRanking2 < 10; nCntRanking2++)
			{
				fscanf(pFile, "%d", &g_aRanking[nCntRanking].aName[nCntRanking2]);
			}
			
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	//else
	//{//ファイルが開けなかった場合
	//	printf("***エラー:ファイルが開けませんでした***\n");
	//}
	pDevice = GetDevice();	//デバイスの取得

							//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//テクスチャのファイル名
		&g_pTextureRanking);

	//位置の初期化
	g_posRanking = D3DXVECTOR3(720.0f, 120.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 80,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffRanking->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntRanking2 = 0; nCntRanking2 < NUM_RANKING; nCntRanking2++)
	{
		for (nCntRanking = 0; nCntRanking < NUM_PLACE; nCntRanking++)
		{
			pVtx[0].pos.x = g_posRanking.x - 40;	//右回りで設定
			pVtx[0].pos.y = g_posRanking.y - 40;
			pVtx[0].pos.z = g_posRanking.z;
			pVtx[1].pos.x = g_posRanking.x + 40;
			pVtx[1].pos.y = g_posRanking.y - 40;
			pVtx[1].pos.z = g_posRanking.z;
			pVtx[2].pos.x = g_posRanking.x - 40;
			pVtx[2].pos.y = g_posRanking.y + 40;
			pVtx[2].pos.z = g_posRanking.z;
			pVtx[3].pos.x = g_posRanking.x + 40;
			pVtx[3].pos.y = g_posRanking.y + 40;
			pVtx[3].pos.z = g_posRanking.z;

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
			g_posRanking.x += 40;
		}
		g_posRanking.x -= 320;
		g_posRanking.y += 45;
	}




	

	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();
}
//ポリゴンの終了処理
void UninitRanking(void)
{
	int nCnt, nCnt2;
	int aName[MAX_NAME];

	GetRankingname(aName);

	for (nCnt = 0; nCnt < NUM_RANKING; nCnt++)
	{
		if (g_aRanking[nCnt].bPlayer == true)
		{
			for (nCnt2 = 0; nCnt2 < MAX_NAME; nCnt2++)
			{
				g_aRanking[nCnt].aName [nCnt2]= aName[nCnt2];
			}
			

		}
	}

	FILE*pFile;//ファイルポインタを宣言

			   //ファイルを開く
	pFile = fopen("ranking.txt", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //ファイルに入力された構造体の要素を出力する

	 /*fread(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/

		for (nCnt= 0; nCnt < NUM_RANKING; nCnt++)
		{
			fprintf(pFile, "%d\n", g_aRanking[nCnt].nScore);
			for (nCnt2 = 0; nCnt2 < 10; nCnt2++)
			{
				fprintf(pFile, "%d\n", g_aRanking[nCnt].aName[nCnt2]);
			}
		}
	}
	//ファイルを閉じる
	fclose(pFile);

	//テクスチャの破棄
	if (g_pTextureRanking != NULL)
	{

		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	//テクスチャの破棄
	if (g_pVtxBuffRanking != NULL)
	{

		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}
//ポリゴンの更新処理
void UpdateRanking(void)
{
	int nCntRanking, nCntRanking2, nNum1, nNum2;
	int aTexU[NUM_PLACE*NUM_RANKING] = {};	//各桁の数字を格納
	int aTexV[NUM_PLACE*NUM_RANKING] = {};
	int nCount1, nCount2, nData;
	int nScore = GetScore();
	int aName[MAX_NAME];
	int aNameData[MAX_NAME] = {}, aData[MAX_NAME];

	////=====================================================================
	////ソート処理
	////=====================================================================
	for (nCount1 = 0; nCount1 < NUM_RANKING; nCount1++)
	{
		if (nScore > g_aRanking[nCount1].nScore)
		{
			nData = nScore;
			nScore = g_aRanking[nCount1].nScore;
			g_aRanking[nCount1].nScore = nData;

			for (nCount2 = 0; nCount2 < MAX_NAME; nCount2++)
			{
				aData[nCount2] = aNameData[nCount2];
				aNameData[nCount2] = g_aRanking[nCount1].aName[nCount2];
				g_aRanking[nCount1].aName[nCount2] = aData[nCount2];
			}

			if (g_bPlayerSet == false)
			{
				
				g_aRanking[nCount1].bPlayer = true;
				g_bPlayerSet = true;
			}
			
		}
	}

	/*for (nCount1 = 0; nCount1 <NUM_RANKING; nCount1++)
	{
		for (nCount2 = nCount1 + 1; nCount2 < NUM_RANKING; nCount2++)
		{
			if (g_aRanking[nCount1].nScore < g_aRanking[nCount2].nScore)
			{
				nData = g_aRanking[nCount1].nScore;
				g_aRanking[nCount1].nScore = g_aRanking[nCount2].nScore;
				g_aRanking[nCount2].nScore = nData;
			}
		}

	}*/
	//=====================================================================

	for (nCntRanking2 = 0; nCntRanking2 < NUM_RANKING; nCntRanking2++)
	{
		for (nCntRanking = 0; nCntRanking < NUM_PLACE; nCntRanking++)
		{

			nNum1 = pow(10, nCntRanking + 1);
			nNum2 = pow(10, nCntRanking);
			aTexU[nCntRanking+(8*nCntRanking2)] = (g_aRanking[nCntRanking2].nScore % nNum1) / nNum2;
		}
	}
	

	//テクスチャの更新
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffRanking->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntRanking2 = 0; nCntRanking2 < NUM_RANKING; nCntRanking2++)
	{
		/*pVtx += 28;*/
		for (nCntRanking = 7; nCntRanking >= 0; nCntRanking--)
		{
			//テクスチャの座標の設定
			pVtx[0].tex = D3DXVECTOR2(aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f) + 0.1f, 1.0f);

			pVtx += 4;
		}
		/*pVtx += 32;*/
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();


	
}
//ポリゴンの描画処理
void DrawRanking(void)
{
	int nCntRanking;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

								//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	for (nCntRanking = 0; nCntRanking < 80; nCntRanking++)
	{
		//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRanking * 4, 2);
	}
	

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	2,//プリミティブ（ポリゴン）の数
	//	&g_aVertex[0],//頂点情報の先頭アドレス
	//	sizeof(VERTEX_2D));//頂点情報構造体のサイズ
}
//スコアの設定処理
void SetRanking(int nRanking)
{
	int aTexU[NUM_PLACE];	//各桁の数字を格納
	int nCntRanking;


}
Ranking* GetRanking(void)
{
	return &g_aRanking[0];
}