//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 澗口将太郎
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_BOMB,		// ボム発射音
	SOUND_LABEL_SE_BREAK00,		// ブレイク音
	SOUND_LABEL_SE_BREAK01,		// 撃破音
	SOUND_LABEL_SE_BREAK02,		// 撃破音
	SOUND_LABEL_SE_HITPLAYER,	// 被弾音
	SOUND_LABEL_SE_SHOT01,	// 敵発射音１
	SOUND_LABEL_SE_SHOT02,	// 敵発射音２
	SOUND_LABEL_SE_CANCEL,	// キャンセル音
	SOUND_LABEL_SE_COLLECT,	// 決定音
	SOUND_LABEL_SE_SELECT,	// 選択音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
