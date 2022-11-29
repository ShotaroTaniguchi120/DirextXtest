#ifndef _Rankingname_h_	//このマクロが定義されていなければ
#define _Rankingname_h_	//二重インクルード防止マクロ

#include "main.h"
#define MAX_NAME (10)
//プロトタイプ宣言
void InitRankingname(void);
void UninitRankingname(void);
void UpdateRankingname(void);
void DrawRankingname(void);
void GetRankingname(int aName[MAX_NAME]);
bool GetInputfrag(void);


#endif // !_Rankingname_h_