#ifndef _Explosion_h_	//このマクロが定義されていなければ
#define _Explosion_h_	//二重インクルード防止マクロ

#include "main.h"

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);

#endif // !_Explosion_h_