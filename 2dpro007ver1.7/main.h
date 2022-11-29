#ifndef  _MAIN_H_	//このマクロ定義がされていなかったら
#define _MAIN_H_	//二重インクルード防止のマクロを定義する
#include<Windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対処マクロ
#include "dinput.h" //入力処理に必要
#include "xaudio2.h"	//サウンド処理に必要
#include<time.h>
#include<stdio.h>

//ライブラリのリンク
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")	//システム時刻取得に必要
#pragma comment (lib,"dinput8.lib")	//入力処理に必要
#pragma comment (lib,"dxguid.lib")	//入力処理に必要


//マクロ定義
#define ID_BUTTON_FINISH (101)//終了ボタンのID
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (960)
#define GAMEAREA_MIN (20)
#define GAMEAREA_WIDTH_MAX (820)
#define GAMEAREA_HEIGHT_MAX (940)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;		//座標変換係数（1.0fで固定）
	D3DCOLOR col;	//頂点カラー
	D3DXVECTOR2 tex;
}VERTEX_2D;

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX
}MODE;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);


#endif // ! _MAIN_H_



