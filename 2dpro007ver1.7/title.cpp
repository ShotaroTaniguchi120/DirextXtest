#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
//#include "padinput.h"
#include "sound.h"

//�}�N����`
#define MAX_TEX (2)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
bool g_Select = false;
bool g_EndFrag = false;

//�|���S���̏���������
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntTitle;

	//�T�E���h�̐���
	PlaySound(SOUND_LABEL_BGM000);

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title00.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title01.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureTitle[1]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*MAX_TEX * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�E���Őݒ�
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 960.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 960.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�e�N�X�`���̏ꍇ�S�Ĕ���
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}
//�|���S���̏I������
void UninitTitle(void)
{
	int nCntTitle;

	for (nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	
	//�e�N�X�`���̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//�|���S���̍X�V����
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_Select = g_Select ^ 1;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_Z) == true || GetKeyboardTrigger(DIK_SPACE) == true)
	{//ENTER�L�[�������ꂽ

		if (g_Select == false)
		{
			//���[�h�ݒ�i�Q�[����ʂɈڍs�j
			SetFade(MODE_GAME);
		}
		else if (g_Select == true)
		{
			g_EndFrag = true;
		}
	}
}
//�|���S���̕`�揈��
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle[g_Select]);

	
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
	

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}
bool GetFrag(void)
{
	return g_EndFrag;
}