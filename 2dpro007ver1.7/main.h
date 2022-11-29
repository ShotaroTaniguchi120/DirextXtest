#ifndef  _MAIN_H_	//���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_	//��d�C���N���[�h�h�~�̃}�N�����`����
#include<Windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ώ��}�N��
#include "dinput.h" //���͏����ɕK�v
#include "xaudio2.h"	//�T�E���h�����ɕK�v
#include<time.h>
#include<stdio.h>

//���C�u�����̃����N
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")	//�V�X�e�������擾�ɕK�v
#pragma comment (lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment (lib,"dxguid.lib")	//���͏����ɕK�v


//�}�N����`
#define ID_BUTTON_FINISH (101)//�I���{�^����ID
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (960)
#define GAMEAREA_MIN (20)
#define GAMEAREA_WIDTH_MAX (820)
#define GAMEAREA_HEIGHT_MAX (940)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;		//���W�ϊ��W���i1.0f�ŌŒ�j
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;
}VERTEX_2D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_MAX
}MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);


#endif // ! _MAIN_H_



