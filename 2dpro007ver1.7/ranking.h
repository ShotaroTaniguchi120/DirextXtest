#ifndef _Ranking_h_	//このマクロが定義されていなければ
#define _Ranking_h_	//二重インクルード防止マクロ

#include "main.h"

//構造体の定義
typedef struct
{
	int nScore = 0;
	int aName[10] = {};
	bool bPlayer = false;
}Ranking;


//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRanking(int nRanking);
Ranking* GetRanking(void);


#endif // !_Ranking_h_