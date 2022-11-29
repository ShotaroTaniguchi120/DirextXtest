//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���������Y
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_BOMB,		// �{�����ˉ�
	SOUND_LABEL_SE_BREAK00,		// �u���C�N��
	SOUND_LABEL_SE_BREAK01,		// ���j��
	SOUND_LABEL_SE_BREAK02,		// ���j��
	SOUND_LABEL_SE_HITPLAYER,	// ��e��
	SOUND_LABEL_SE_SHOT01,	// �G���ˉ��P
	SOUND_LABEL_SE_SHOT02,	// �G���ˉ��Q
	SOUND_LABEL_SE_CANCEL,	// �L�����Z����
	SOUND_LABEL_SE_COLLECT,	// ���艹
	SOUND_LABEL_SE_SELECT,	// �I����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
