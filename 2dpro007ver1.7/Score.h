#ifndef _Score_h_	//このマクロが定義されていなければ
#define _Score_h_	//二重インクルード防止マクロ

#include "main.h"

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(D3DXVECTOR3 pos);
void AddScore(int *pValue);
int GetScore(void);

#endif // !_Score_h_